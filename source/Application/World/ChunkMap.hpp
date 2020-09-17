#pragma once
#include <map>
#include <SFML/System.hpp>
#include "../Vector3LessThan/Vector3LessThan.hpp"

class Chunk;
typedef std::map<sf::Vector3<int64_t>, Chunk, Vector3LessThan<int64_t>> ChunkMap;
#include "Chunk/Chunk.hpp" // AAAA I HATE CPP PLEASE KILL ME
