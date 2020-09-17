#pragma once

#include <cstdint>
#include <vector>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "../PlaneVertex.hpp"

class RenderChunk {
    private:
        sf::Vector3<int64_t> chunkPosition;
        uint32_t vaoId = 0;
        uint32_t vboId = 0;
        uint32_t iboId = 0;
        uint32_t triangleAmount = 0;
    public:
        explicit RenderChunk(sf::Vector3<int64_t> chunkPosition);
        ~RenderChunk();
        void update(const std::vector<PlaneVertex>& vertexData, const std::vector<uint32_t>& indexData);
        void draw(uint32_t blockTexture, sf::Vector3<double> playerPosition, sf::Shader& chunkShader) const;
};
