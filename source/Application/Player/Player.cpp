
#include "Player.hpp"

void Player::computeMatricesMouse(sf::Window& window) {
    if (grabbed) {
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2i mousePosCenter = sf::Vector2i(window.getSize() / 2u);
        sf::Vector2i offset = mousePosCenter - mousePos;
        sf::Mouse::setPosition(mousePosCenter, window);
        horizontalAngle += mouseSpeed * (float) offset.x;
        verticalAngle += mouseSpeed * (float) offset.y;
        verticalAngle = verticalAngle > glm::radians(89.9f) ? glm::radians(89.9f) : verticalAngle;
        verticalAngle = verticalAngle < glm::radians(-89.9f) ? glm::radians(-89.9f) : verticalAngle;
        direction = glm::vec3(
                std::cos(verticalAngle) * std::sin(horizontalAngle),
                std::sin(verticalAngle),
                std::cos(verticalAngle) * std::cos(horizontalAngle)
        );
        glm::vec3 playerPosition_glm(playerPos.x, playerPos.y, playerPos.z);
        glm::mat4 view = glm::lookAt(glm::vec3(), direction.load(), glm::vec3(0, 1, 0));
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.1f, 10000.0f);
        this->view = view;
        this->projection = projection;
        matrix = projection * view;
    }
}

void Player::computePlayerPosKeyboard(sf::Window& window, float deltaTime) {
    //direction.y = 0;
    glm::vec3 current_direction = glm::normalize(direction.load());
    if (sf::Keyboard::isKeyPressed(forward)) {
        glm::vec3 poffset(current_direction * cameraSpeed * deltaTime);
        playerPos += sf::Vector3<double>(poffset.x, 0, poffset.z);
    }
    if (sf::Keyboard::isKeyPressed(backward)) {
        glm::vec3 poffset(current_direction * cameraSpeed * deltaTime);
        playerPos -= sf::Vector3<double>(poffset.x, 0, poffset.z);
    }
    if (sf::Keyboard::isKeyPressed(left)) {
        glm::vec3 poffset(glm::normalize(glm::cross(current_direction, glm::vec3(0, 1, 0))) * cameraSpeed * deltaTime);
        playerPos -= sf::Vector3<double>(poffset.x, 0, poffset.z);
    }
    if (sf::Keyboard::isKeyPressed(right)) {
        glm::vec3 poffset(glm::normalize(glm::cross(current_direction, glm::vec3(0, 1, 0))) * cameraSpeed * deltaTime);
        playerPos += sf::Vector3<double>(poffset.x, 0, poffset.z);
    }
    if (sf::Keyboard::isKeyPressed(up)) {
        playerPos += sf::Vector3<double>(0, 1, 0) * (double) (deltaTime * cameraSpeed);
    }
    if (sf::Keyboard::isKeyPressed(down)) {
        playerPos -= sf::Vector3<double>(0, 1, 0) * (double) (deltaTime * cameraSpeed);
    }
    direction.store(current_direction);
}

void Player::setGrabbed(bool grabbed_) {
    grabbed = grabbed_;
}

glm::mat4 Player::getViewMatrix() {
    return view;
}

glm::mat4 Player::getProjectionMatrix() {
    return projection;
}

glm::mat4 Player::getVpMatrix() {
    return matrix;
}
sf::Vector3<double> Player::getPlayerPos() {
    return playerPos;
}
sf::Vector3f Player::getDirection() const {
    glm::vec3 current_direction = direction.load();
    return sf::Vector3f(current_direction.x, current_direction.y, current_direction.z);
}
