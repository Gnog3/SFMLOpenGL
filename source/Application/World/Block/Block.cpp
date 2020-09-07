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

bool Block::isBlock() {
    return true;
}
void Block::genVertices(sf::Vector3<uint8_t> blockPosition, Adjoins adjoins, std::vector<RenderPlane>& vertices) {
    uint32_t adjoinsAmount = adjoins.amount();
    if (adjoinsAmount == 6)
        return;
    Adjoins sides = ~adjoins;
    constexpr bool (Adjoins::* funcs[])() const {
            &Adjoins::isUp,
            &Adjoins::isDown,
            &Adjoins::isLeft,
            &Adjoins::isRight,
            &Adjoins::isFront,
            &Adjoins::isBack
    };
    uint32_t x = id % 16;
    uint32_t y = id / 16;
    sf::Vector2f texCoords((float) x / 16.0f, (float) y / 16.0f);
    for_range<0, 6>([&]<auto i>() {
        if ((sides.*funcs[i])()) {
            RenderPlane rp;
            rp.position = (sf::Vector3f) blockPosition;
            rp.texture = texCoords;
            rp.direction.x = offset[i][0];
            rp.direction.y = offset[i][1];
            rp.direction.z = offset[i][2];
            rp.normal = i;
            vertices.push_back(rp);
        }
    });
}
