#pragma once

#include <cstdint>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>

#pragma pack(push, 0)

struct RenderPlane {
    sf::Vector3f position;           // 12 bytes
    sf::Vector2f texture;            // 8 bytes
    sf::Vector3<int8_t> direction;   // 3 bytes
    uint8_t normal = 0;              // 1 byte
};

#pragma pack(pop)