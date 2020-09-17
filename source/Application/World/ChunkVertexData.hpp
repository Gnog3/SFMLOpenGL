#pragma once
#include <vector>
#include <cstdint>
#include "../Engine/PlaneVertex.hpp"

struct ChunkVertexData {
    std::vector<PlaneVertex> vertexData;
    std::vector<uint32_t> indexData;
    ChunkVertexData() = default;
    ChunkVertexData(ChunkVertexData&& other) noexcept {
        vertexData = std::move(other.vertexData);
        indexData = std::move(other.indexData);
    }
};
