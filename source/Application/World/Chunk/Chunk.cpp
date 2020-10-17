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
constexpr int Chunk::getPlane(int sign, int offset) {
    switch (sign) {
        case -1:
            switch (offset) {
                case 0:
                    return 2;
                case 1:
                    return 1;
                case 2:
                    return 5;
                default:
                    std::exit(-1);
            }
        case 1:
            switch (offset) {
                case 0:
                    return 3;
                case 1:
                    return 0;
                case 2:
                    return 4;
                default:
                    std::exit(-1);
            }
        default:
            break;
    }
    std::exit(-1);
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
    sf::Vector2f texCoords;
    for (auto& iter : blockMap) {
        using veci = sf::Vector3<int8_t>;
        using vecu = sf::Vector3<uint8_t>;
        auto block = iter.second;
        auto pos = (sf::Vector3<int8_t>) iter.first;
        bool calculated = false;
        for_values<-1, 1>([&]<auto i>() {
            for_values<0, 1, 2>([&]<auto j>() {
                veci combined = pos;
                *(((int8_t*) &combined) + j) += i;
                if (!isBlockInside(combined) || blockMap.find(static_cast<vecu>(combined)) == blockMap.end()) {
                    if (!calculated) {
                        uint8_t id = block.getId();
                        uint32_t x = id % 16;
                        uint32_t y = id / 16;
                        texCoords = sf::Vector2f((float) x / 16.0f, (float) y / 16.0f);
                    }
                    constexpr int side = getPlane(i, j);
                    block.genVertices<side>(iter.first, chunkVertexData, texCoords);
                }
            });
        });
    }
    
    return chunkVertexData;
}
bool Chunk::empty() const {
    return blockMap.empty();
}
