#include "Vector3LessThan.hpp"

template<class T>
bool Vector3LessThan<T>::operator()(const sf::Vector3<T>& v1, const sf::Vector3<T>& v2) const {
    return false;
}