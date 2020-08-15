#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-default-arguments"

#include <iostream>
#include "StaticBlockFragmentContainer.hpp"

StaticBlockFragmentContainer::StaticBlockFragmentContainer(std::string& texturePath) {
    sf::Image image;
    image.loadFromFile(texturePath);
    sf::Vector2u size = image.getSize();
    glGenVertexArrays(1, &vaoid);
    glBindVertexArray(vaoid);
    glGenBuffers(1, &vboid);
    glBindBuffer(GL_ARRAY_BUFFER, vboid);
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
};

StaticBlockFragmentContainer::~StaticBlockFragmentContainer() {
    glDeleteTextures(1, &textureId);
    glDeleteBuffers(1, &vboid);
    glDeleteVertexArrays(1, &vaoid);
}

ThingContainerTypeType StaticBlockFragmentContainer::typeType() {
    return ThingContainerTypeType::StaticBlock;
}
void StaticBlockFragmentContainer::addBlock(sf::Vector3i position, uint32_t state) {
    //rebuilt = true;
    //std::vector<std::pair<sf::Vector3i, Thing>> adjoiningBlocks = getAdjoiningBlocks(position);
    fragments.emplace_back();
    fragments.back().addBlock(position);
}
void StaticBlockFragmentContainer::removeBlock(sf::Vector3i position) {
    rebuilt = true;
}
void StaticBlockFragmentContainer::draw() {
    if (rebuilt) {
        rebuilt = false;
        size_t size = 0;
        for (auto& fragment : fragments) {
            size += fragment.getSize();
        }
        std::cout << size << std::endl;
        glBindVertexArray(vaoid);
        glBindBuffer(GL_ARRAY_BUFFER, vboid);
        glBindTexture(GL_TEXTURE_2D, textureId);
        if (size != vertexSize) {
            glBufferData(GL_ARRAY_BUFFER, size * 4, nullptr, GL_STATIC_DRAW);
            vertexSize = size;
        }
        auto ptr = (float*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        uint32_t offset = 0;
        for (auto& fragment : fragments) {
            std::vector<float>& vector = fragment.getVertices();
            float* data = vector.data();
            size_t amount = vector.size();
            std::memcpy(ptr + offset, data, amount * 4);
            offset += amount;
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (5 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    } else {
        glBindVertexArray(vaoid);
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
//    glDrawElements(GL_TRIANGLES, vertexSize, GL_UNSIGNED_INT, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, vertexSize / 3);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

#pragma clang diagnostic pop