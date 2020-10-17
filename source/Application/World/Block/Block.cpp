#include <chrono>
#include "Block.hpp"

sf::Vector3<uint8_t> Block::getPositionChunkRel(sf::Vector3<int64_t> blockPosition) {
    blockPosition.x = blockPosition.x < 0 ? (16 + (blockPosition.x % 16)) % 16 : blockPosition.x % 16;
    blockPosition.y = blockPosition.y < 0 ? (16 + (blockPosition.y % 16)) % 16 : blockPosition.y % 16;
    blockPosition.z = blockPosition.z < 0 ? (16 + (blockPosition.z % 16)) % 16 : blockPosition.z % 16;
#ifdef DEBUG
    assert(blockPosition.x <= 15);
    assert(blockPosition.y <= 15);
    assert(blockPosition.z <= 15);
    assert(blockPosition.x >= 0);
    assert(blockPosition.y >= 0);
    assert(blockPosition.z >= 0);
#endif
    return (sf::Vector3<uint8_t>) blockPosition;
}

Block::Block(uint8_t id) : id(id) {}

uint8_t Block::getId() const {
    return id;
}
