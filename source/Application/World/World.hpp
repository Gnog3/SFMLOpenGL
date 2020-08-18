#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "../ogl.hpp"
#include "../Player/Player.hpp"
#include "../Vector3LessThan/Vector3LessThan.hpp"
#include "SkyBox/SkyBox.hpp"
#include "OpenGLModel/OpenGLModel.hpp"
#include "Chunk/Chunk.hpp"
#include "ChunkMap.hpp"

class World {
    private:
        sf::Shader shader;
        std::unique_ptr<SkyBox> skyBox;
        ChunkMap chunkMap;
        std::unique_ptr<Chunk> chunk;
        uint32_t blockTexture = 0;
    public:
        World();
        ~World();
        void draw(Player& player);
};

