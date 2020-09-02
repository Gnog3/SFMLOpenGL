#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <glm.hpp>
#include <tuple>
#include "../ogl.hpp"
#include "../Player/Player.hpp"
#include "../Vector3LessThan/Vector3LessThan.hpp"
#include "SkyBox/SkyBox.hpp"
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
    bool isFound;
};
class Client;
class World {
    private:
        sf::Shader chunkShader;
        std::unique_ptr<SkyBox> skyBox;
        NotConstructed<Crosshair, true> crosshair;
        uint32_t blockTexture = 0;
        ChunkMap chunkMap;
    public:
        World();
        ~World();
        Block* getBlock(sf::Vector3<int64_t> position);
        RayCastResult rayCast(sf::Vector3<double> position, sf::Vector3f direction, float maxDist);
        void draw(Player& player);
        void placeBlock(std::unique_ptr<Block> block, sf::Vector3<int64_t> position);
        void removeBlock(sf::Vector3<int64_t> position);
        
        friend Client;
};
