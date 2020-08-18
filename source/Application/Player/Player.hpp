#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <glm.hpp>
#include <gtx/transform.hpp>
class Player {
    private:
        float horizontalAngle = 3.14f;
        float verticalAngle = 0.0f;
        float FoV = 70.0f;
        float cameraSpeed = 10.0f;
        float mouseSpeed = 0.002f;
        sf::Vector3<double> playerPos = sf::Vector3<double>();
        
        glm::vec3 direction = glm::vec3();
        glm::mat4 view = glm::mat4();
        glm::mat4 projection = glm::mat4();
        glm::mat4 matrix = glm::mat4();
        
        sf::Keyboard::Key forward = sf::Keyboard::W;
        sf::Keyboard::Key backward = sf::Keyboard::S;
        sf::Keyboard::Key left = sf::Keyboard::A;
        sf::Keyboard::Key right = sf::Keyboard::D;
        sf::Keyboard::Key down = sf::Keyboard::LShift;
        sf::Keyboard::Key up = sf::Keyboard::Space;
        
    public:
        void computeMatricesMouse(sf::Window& window);
        void computePlayerPosKeyboard(sf::Window& window, float deltaTime);
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
        glm::mat4 getVpMatrix();
        sf::Vector3<double> getPlayerPos();
};
