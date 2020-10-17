#pragma once

#include <map>
#include <mutex>
#include <vector>
#include <SFML/Graphics.hpp>
#include <functional>
#include <GL/glew.h>
#include "../../Vector3LessThan/Vector3LessThan.hpp"
#include "../Block/Block.hpp"
#include "../ChunkMap.hpp"
#include "../../Engine/PlaneVertex.hpp"
#include "../ChunkVertexData.hpp"

class Chunk {
    private:
        using AdjoinsSetFunc = void (Adjoins::*)();
        using Vector3l = sf::Vector3<int64_t>;
        std::map<sf::Vector3<uint8_t>, Block, Vector3LessThan<uint8_t>> blockMap;
        sf::Vector3i chunkPosition;
        [[nodiscard]] bool isBlockInside(Vector3l blockPosition) const;
        static bool isBlockInside(sf::Vector3<int8_t> blockPosition);
        static AdjoinsSetFunc getFunc(int offset, int coordinate);
        static constexpr int getPlane(int sign, int offset);
    public:
        static sf::Vector3i getChunk(Vector3l blockPosition);
        Chunk() = default;
        explicit Chunk(sf::Vector3i chunkPosition);
        [[nodiscard]] Block* getBlock(sf::Vector3<uint8_t> blockPosition);
        void placeBlock(sf::Vector3<uint8_t> position, uint8_t id);
        void removeBlock(sf::Vector3<uint8_t> position);
        [[nodiscard]] ChunkVertexData calculateVertices(const ChunkMap& chunkMap);
        [[nodiscard]] bool empty() const;
};
