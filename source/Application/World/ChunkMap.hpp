#pragma once
#include <map>
#include <SFML/System.hpp>
#include "../Vector3LessThan/Vector3LessThan.hpp"

class Chunk;
typedef std::map<sf::Vector3i, Chunk, Vector3LessThan<int>> ChunkMap;
#include "Chunk/Chunk.hpp" // AAAA I HATE CPP PLEASE KILL ME
