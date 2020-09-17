#include "RenderChunk.hpp"
#include <iostream>
RenderChunk::RenderChunk(sf::Vector3<int64_t> chunkPosition) {
    this->chunkPosition = chunkPosition;
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
RenderChunk::~RenderChunk() {
    glDeleteBuffers(1, &vboId);
    glDeleteBuffers(1, &iboId);
    glDeleteVertexArrays(1, &vaoId);
}
void RenderChunk::update(const std::vector<PlaneVertex>& vertexData, const std::vector<uint32_t>& indexData) {
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(PlaneVertex), vertexData.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(uint32_t), indexData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    triangleAmount = indexData.size();
}
void RenderChunk::draw(uint32_t blockTexture, sf::Vector3<double> playerPosition, sf::Shader& chunkShader) const {
    glBindVertexArray(vaoId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBindTexture(GL_TEXTURE_2D, blockTexture);
    sf::Vector3f offset = (sf::Vector3f) (sf::Vector3<double>(chunkPosition) - playerPosition);
//    std::cout << chunkPosition.z << std::endl;
    chunkShader.setUniform("chunkPosition", offset);
    glDrawElements(GL_TRIANGLES, triangleAmount, GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}
