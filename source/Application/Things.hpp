#pragma once
#include <map>
#include <SFML/System/Vector3.hpp>
#include "World/IThingContainer/IThingContainer.hpp"
#include "Thing.hpp"
#include "Vector3LessThan/Vector3LessThan.hpp"
typedef std::map<sf::Vector3i, std::pair<ThingContainerTypeType, Thing>, Vector3LessThan<int>> Things;