#include "Vector3LessThan.hpp"

template<class T>
bool Vector3LessThan<T>::operator()(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2) const {
    if (v1.x < v2.x) return true;
    if (v1.x > v2.x) return false;
    if (v1.y < v2.y) return true;
    if (v1.y > v2.y) return false;
    return v1.z < v2.z;
}