#pragma once

#include <atomic>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <glm.hpp>
#include <gtx/transform.hpp>

class Player {
    private:
        float horizontalAngle = 3.14f;
        float verticalAngle = 0.0f;
        float FoV = 70.0f;
        float cameraSpeed = 12.5f;
        float mouseSpeed = 0.002f;
        bool grabbed = true;
        sf::Vector3<double> playerPos = sf::Vector3<double>();
        
        std::atomic<glm::vec3> direction;
        std::atomic<glm::mat4> view;
        std::atomic<glm::mat4> projection;
        std::atomic<glm::mat4> matrix;
        
        sf::Keyboard::Key forward = sf::Keyboard::W;
        sf::Keyboard::Key backward = sf::Keyboard::S;
        sf::Keyboard::Key left = sf::Keyboard::A;
        sf::Keyboard::Key right = sf::Keyboard::D;
        sf::Keyboard::Key down = sf::Keyboard::LShift;
        sf::Keyboard::Key up = sf::Keyboard::Space;
    
    public:
        void computeMatricesMouse(sf::Window& window);
        void computePlayerPosKeyboard(sf::Window& window, float deltaTime);
        void setGrabbed(bool grabbed_);
        [[nodiscard]] glm::mat4 getViewMatrix();
        [[nodiscard]] glm::mat4 getProjectionMatrix();
        [[nodiscard]] glm::mat4 getVpMatrix();
        [[nodiscard]] sf::Vector3<double> getPlayerPos();
        [[nodiscard]] sf::Vector3f getDirection() const;
};
