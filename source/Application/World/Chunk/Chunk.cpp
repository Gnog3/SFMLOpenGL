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
Chunk::Chunk(sf::Vector3i chunkPosition, uint32_t planeVbo) : chunkPosition(chunkPosition) {
    glGenVertexArrays(1, &vaoId);
    glGenBuffers(1, &vboId);
    glBindVertexArray(vaoId);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glBindBuffer(GL_ARRAY_BUFFER, planeVbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 40, (void*) nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 40, (void*) (2 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 40, (void*) (4 * sizeof(float)));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 40, (void*) (7 * sizeof(float)));
    glVertexAttribIPointer(4, 3, GL_BYTE,           40, (void*) (9 * sizeof(float)));
    glVertexAttribIPointer(5, 1, GL_UNSIGNED_BYTE,  40, (void*) (9 * sizeof(float) + 3 * sizeof(int8_t)));
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
Block* Chunk::getBlock(sf::Vector3<uint8_t> blockPosition) {
    auto search = blockMap.find(blockPosition);
    return search != blockMap.end() ? search->second.get() : nullptr;
}
void Chunk::placeBlock(sf::Vector3<uint8_t> position, std::unique_ptr<Block> block) {
    auto& node = blockMap[position];
    node = nullptr;
    node.swap(block);
    changed = true;
}
void Chunk::removeBlock(sf::Vector3<uint8_t> position) {
    blockMap.erase(position);
    changed = true;
}
void Chunk::sendVertices() {
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, planeData.size() * sizeof(RenderPlane), planeData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    triangles = planeData.size();
    std::vector<RenderPlane>().swap(planeData);
    send_require = false;
}
void Chunk::calculateVertices(const ChunkMap& chunkMap) {
    if (!planeData.empty()) {
        std::vector<RenderPlane>().swap(planeData);
    }
    for (auto& iter : blockMap) {
        using veci = sf::Vector3<int8_t>;
        using vecu = sf::Vector3<uint8_t>;
        auto block = *iter.second;
        auto pos = (sf::Vector3<int8_t>) iter.first;
        Adjoins adjoins;
        for_values<-1, 1>([&]<auto i>() {
            for_values<0, 1, 2>([&]<auto j>() {
                veci combined = pos;
                *(((int8_t*) &combined) + j) += i;
                if (isBlockInside(combined)) {
                    auto iter = blockMap.find(static_cast<vecu>(combined));
                    if (iter != blockMap.end()) {
                        if (iter->second->isBlock()) {
                            (adjoins.*Chunk::getFunc(i, j))();
                        }
                    }
                }
            });
        });
        block.genVertices(iter.first, adjoins, planeData);
    }
    changed = false;
    send_require = true;
}
bool Chunk::getChanged() const {
    return changed;
}
bool Chunk::getSendRequire() const {
    return send_require;
}
bool Chunk::empty() const {
    return blockMap.empty();
}
void Chunk::draw(uint32_t blocksTexture, sf::Vector3<double> playerPosition, sf::Shader& chunkShader) const {
    glBindVertexArray(vaoId);
    glBindTexture(GL_TEXTURE_2D, blocksTexture);
    sf::Vector3f offset =
            (sf::Vector3f) (sf::Vector3<double>((sf::Vector3<int64_t>) chunkPosition * 16ll) - playerPosition);
    chunkShader.setUniform("chunkPosition", offset);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, triangles);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
