#pragma once
#include <map>
#include <mutex>
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>
#include "../../Vector3LessThan/Vector3LessThan.hpp"
#include "../../ogl.hpp"
#include "../Block/Block.hpp"
#include "../ChunkMap.hpp"
class Chunk {
    private:
        using AdjoinsSetFunc = void (Adjoins::* )();
        using Vector3l = sf::Vector3<int64_t>;
        std::map<sf::Vector3<uint8_t>, std::unique_ptr<Block>, Vector3LessThan<uint8_t>> blockMap;
        std::vector<float> vertexData;
        std::vector<uint32_t> indexData;
        sf::Vector3i chunkPosition;
        uint32_t vaoId = 0;
        uint32_t vboId = 0;
        uint32_t iboId = 0;
        volatile bool changed = false;
        volatile bool computed = false;
        
        bool isBlockInside(Vector3l blockPosition) const;
        static bool isBlockInside(sf::Vector3<int8_t> blockPosition);
        static AdjoinsSetFunc getFunc(int offset, int coordinate);
    public:
        static sf::Vector3i getChunk(Vector3l blockPosition);
        Chunk(sf::Vector3i chunkPosition);
        void placeBlock(sf::Vector3<uint8_t> position, std::unique_ptr<Block>&& block);
        void calculateVertices(const ChunkMap& chunkMap);
        void sendVertices();
        void draw(uint32_t blocksTexture) const;
};
