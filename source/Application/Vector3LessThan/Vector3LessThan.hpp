#pragma once
#include <SFML/System.hpp>
template <class T>
class Vector3LessThan {
    public:
        bool operator()(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2) const {
            if (v1.x < v2.x) return true;
            if (v1.x > v2.x) return false;
            if (v1.y < v2.y) return true;
            if (v1.y > v2.y) return false;
            return v1.z < v2.z;
        }
};

template<>
class Vector3LessThan<uint8_t> {
    public:
        bool operator()(const sf::Vector3<uint8_t>& v1, const sf::Vector3<uint8_t>& v2) const {
            uint32_t first = *(uint32_t*) &v1;
            uint32_t second = *(uint32_t*) &v2;
            first &= 0xFFFFFFu;
            second &= 0xFFFFFFu;
            return first < second;
        }
};
