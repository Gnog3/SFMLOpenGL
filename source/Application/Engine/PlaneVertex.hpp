#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
struct PlaneVertex {
    sf::Vector3f position __attribute__((packed));
    sf::Vector3f normal __attribute__((packed));
    sf::Vector2f texCoord __attribute__((packed));
    PlaneVertex& operator=(const PlaneVertex&) = default;
};