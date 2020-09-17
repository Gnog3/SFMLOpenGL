#include <iostream>
#include "Chunk.hpp"
bool Chunk::isBlockInside(Vector3l blockPosition) const {
    return getChunk(blockPosition) == chunkPosition;
}
bool Chunk::isBlockInside(sf::Vector3<int8_t> blockPosition) {
    return blockPosition.x >= 0 &&
           blockPosition.y >= 0 &&
           blockPosition.z >= 0 &&
           blockPosition.x < 16 &&
           blockPosition.y < 16 &&
           blockPosition.z < 16;
}
Chunk::AdjoinsSetFunc Chunk::getFunc(int offset, int coordinate) {
    using functype = std::function<void (Adjoins::*)()>;
    switch (offset) {
        case -1:
            switch (coordinate) {
                case 0:
                    return &Adjoins::setLeft;
                case 1:
                    return &Adjoins::setDown;
                case 2:
                    return &Adjoins::setBack;
                default:
                    break;
            }
            break;
        case 1:
            switch (coordinate) {
                case 0:
                    return &Adjoins::setRight;
                case 1:
                    return &Adjoins::setUp;
                case 2:
                    return &Adjoins::setFront;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return nullptr;
}
sf::Vector3i Chunk::getChunk(Chunk::Vector3l blockPosition) {
    sf::Vector3i chunkPosition = (sf::Vector3i) (blockPosition / 16ll);
    if (blockPosition.x < 0 && blockPosition.x % 16 != 0) chunkPosition.x--;
    if (blockPosition.y < 0 && blockPosition.y % 16 != 0) chunkPosition.y--;
    if (blockPosition.z < 0 && blockPosition.z % 16 != 0) chunkPosition.z--;
    return chunkPosition;
}
Chunk::Chunk(sf::Vector3i chunkPosition) : chunkPosition(chunkPosition) {

}
Block* Chunk::getBlock(sf::Vector3<uint8_t> blockPosition) {
    auto search = blockMap.find(blockPosition);
    return search != blockMap.end() ? &search->second : nullptr;
}
void Chunk::placeBlock(sf::Vector3<uint8_t> position, uint8_t id) {
    try {
        blockMap.at(position);
    } catch (std::out_of_range&) {
        blockMap[position] = Block(id);
        return;
    }
    blockMap[position] = Block(id);
//    std::cout << "Block already exists" << std::endl;
}
void Chunk::removeBlock(sf::Vector3<uint8_t> position) {
    blockMap.erase(position);
}
ChunkVertexData Chunk::calculateVertices(const ChunkMap& chunkMap) {
    ChunkVertexData chunkVertexData;
    for (auto& iter : blockMap) {
        using veci = sf::Vector3<int8_t>;
        using vecu = sf::Vector3<uint8_t>;
        auto block = iter.second;
        auto pos = (sf::Vector3<int8_t>) iter.first;
        Adjoins adjoins;
        for_values<-1, 1>([&]<auto i>() {
            for_values<0, 1, 2>([&]<auto j>() {
                veci combined = pos;
                *(((int8_t*) &combined) + j) += i;
                if (isBlockInside(combined)) {
                    auto iter = blockMap.find(static_cast<vecu>(combined));
                    if (iter != blockMap.end()) {
                        (adjoins.*Chunk::getFunc(i, j))();
                    }
                }
            });
        });
        block.genVertices(iter.first, adjoins, chunkVertexData);
    }

    return chunkVertexData;
}
bool Chunk::empty() const {
    return blockMap.empty();
}
