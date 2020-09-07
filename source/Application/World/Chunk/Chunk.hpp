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
#include "../RenderPlane.hpp"


class Chunk {
    private:
        using AdjoinsSetFunc = void (Adjoins::*)();
        using Vector3l = sf::Vector3<int64_t>;
        std::map<sf::Vector3<uint8_t>, std::unique_ptr<Block>, Vector3LessThan<uint8_t>> blockMap;
//        std::vector<float> vertexData;
//        std::vector<uint32_t> indexData;
        std::vector<RenderPlane> planeData;
        sf::Vector3i chunkPosition;
        uint32_t vaoId = 0;
        uint32_t vboId = 0;
        uint32_t triangles = 0;
        volatile bool changed = false;
        volatile bool send_require = false;
        
        bool isBlockInside(Vector3l blockPosition) const;
        static bool isBlockInside(sf::Vector3<int8_t> blockPosition);
        static AdjoinsSetFunc getFunc(int offset, int coordinate);
    public:
        static sf::Vector3i getChunk(Vector3l blockPosition);
        Chunk() = default;
        Chunk(sf::Vector3i chunkPosition, uint32_t planeVbo);
        Block* getBlock(sf::Vector3<uint8_t> blockPosition);
        void placeBlock(sf::Vector3<uint8_t> position, std::unique_ptr<Block> block);
        void removeBlock(sf::Vector3<uint8_t> position);
        void calculateVertices(const ChunkMap& chunkMap);
        void sendVertices();
        bool getChanged() const;
        bool getSendRequire() const;
        bool empty() const;
        void draw(uint32_t blocksTexture, sf::Vector3<double> playerPosition, sf::Shader& chunkShader) const;
};
