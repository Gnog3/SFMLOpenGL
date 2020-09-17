#pragma once

#include <map>
#include <SFML/System/Vector3.hpp>
#include "RenderChunk/RenderChunk.hpp"
#include "../Vector3LessThan/Vector3LessThan.hpp"

typedef std::map<sf::Vector3<int64_t>, RenderChunk, Vector3LessThan<int64_t>> RenderChunkMap;