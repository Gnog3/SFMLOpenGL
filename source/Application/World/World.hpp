#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "../ogl.hpp"
#include "OpenGLWrappers/VBO/VBO.hpp"
#include "SkyBox/SkyBox.hpp"
#include "../Things.hpp"
#include "ThingContainers.hpp"
#include "../Player/Player.hpp"
#include "OpenGLWrappers/OpenGLModel/OpenGLModel.hpp"
#include "StaticBlockFragmentContainer/StaticBlockFragmentContainer.hpp"
#include "../WorldReferenceHack/WorldReferenceHack.hpp"
class World {
    private:
        sf::Shader shader;
        sf::Shader lightBoxShader;
        uint32_t vaoid = 0;
        VBO<glm::vec3> modelVBO;
        std::optional<SkyBox> skyBox;
    public:
        Things things;
        ThingContainers thingContainers;
        World();
        ~World();
        void draw(Player& player);
        void placeThing(Thing thing, sf::Vector3i position);
};

