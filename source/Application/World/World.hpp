#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "../ogl.hpp"
#include "../Player/Player.hpp"
#include "OpenGLWrappers/VBO/VBO.hpp"
#include "SkyBox/SkyBox.hpp"
#include "OpenGLWrappers/OpenGLModel/OpenGLModel.hpp"
class World {
    private:
        sf::Shader shader;
        sf::Shader lightBoxShader;
        uint32_t vaoid = 0;
        VBO<glm::vec3> modelVBO;
        std::optional<SkyBox> skyBox;
    public:
        World();
        ~World();
        void draw(Player& player);
};

