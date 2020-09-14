#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <glm.hpp>
#include <tuple>
#include <GL/glew.h>
#include "../Player/Player.hpp"
#include "../Vector3LessThan/Vector3LessThan.hpp"
#include "OpenGLModel/OpenGLModel.hpp"
#include "Chunk/Chunk.hpp"
#include "ChunkMap.hpp"
#include "../Timer/Timer.hpp"
#include "../NotConstructed.hpp"
#include "Crosshair/Crosshair.hpp"

struct RayCastResult {
    sf::Vector3<double> end;
    sf::Vector3<int64_t> iend;
    sf::Vector3f norm;
    bool isFound = false;
};

class Client;

class World {
    private:
        ChunkMap chunkMap;
    public:
        World();
        ~World();
        Block* getBlock(sf::Vector3<int64_t> position);
        RayCastResult rayCast(sf::Vector3<double> position, sf::Vector3f direction, float maxDist);
        void draw(Player& player);
        void placeBlock(uint8_t id, sf::Vector3<int64_t> position);
        void removeBlock(sf::Vector3<int64_t> position);
        
        friend Client;
};
