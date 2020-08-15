#pragma once
#include <SFML/System.hpp>
template <class T>
class Vector3LessThan {
    public:
        bool operator()(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2) const;
};
