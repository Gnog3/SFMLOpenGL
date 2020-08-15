#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "../ogl.hpp"
#include "../Player/Player.hpp"
#include "SkyBox/SkyBox.hpp"
#include "OpenGLWrappers/OpenGLModel/OpenGLModel.hpp"
class World {
    private:
        sf::Shader shader;
        std::unique_ptr<SkyBox> skyBox;
    public:
        World();
        ~World();
        void draw(Player& player);
};

