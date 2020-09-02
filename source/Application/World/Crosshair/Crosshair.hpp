#pragma once

#include <SFML/Graphics.hpp>
#include "../../ogl.hpp"

class Crosshair {
    private:
        constexpr static float vertices[] = {
                -0.02f, -0.02f,
                 0.02f,  0.02f,
                -0.02f,  0.02f,
                 0.02f, -0.02f
        };
        sf::Shader shader;
        uint32_t vaoId = 0;
        uint32_t vboId = 0;
    public:
        Crosshair();
        void draw() const;
};



