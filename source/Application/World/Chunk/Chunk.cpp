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
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    glGenBuffers(1, &vboId);
    glGenBuffers(1, &iboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
Block* Chunk::getBlock(sf::Vector3<uint8_t> blockPosition) {
    auto search = blockMap.find(blockPosition);
    return search != blockMap.end() ? &search->second : nullptr;
}
void Chunk::placeBlock(sf::Vector3<uint8_t> position, uint8_t id) {
    blockMap.emplace(position, id);
    changed = true;
}
void Chunk::removeBlock(sf::Vector3<uint8_t> position) {
    blockMap.erase(position);
    changed = true;
}
void Chunk::sendVertices() {
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(uint32_t), indexData.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    triangles = indexData.size();
    std::vector<float>().swap(vertexData);
    std::vector<uint32_t>().swap(indexData);
    
    send_require = false;
}
void Chunk::calculateVertices(const ChunkMap& chunkMap) {
    std::vector<float>().swap(vertexData);
    std::vector<uint32_t>().swap(indexData);
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
        block.genVertices(iter.first, adjoins, vertexData, indexData);
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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBindTexture(GL_TEXTURE_2D, blocksTexture);
    sf::Vector3f offset =
            (sf::Vector3f) (sf::Vector3<double>((sf::Vector3<int64_t>) chunkPosition * 16ll) - playerPosition);
    chunkShader.setUniform("chunkPosition", offset);
    glDrawElements(GL_TRIANGLES, triangles, GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
