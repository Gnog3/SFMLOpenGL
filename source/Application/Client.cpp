#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

#include "Client.hpp"

void Client::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            on = false;
        } else if (event.key.code == sf::Keyboard::Q) {
            P::Window().setMouseCursorGrabbed(false);
            P::Window().setMouseCursorVisible(true);
            P::Player().setGrabbed(false);
        } else if (event.key.code == sf::Keyboard::E) {
            P::Window().setMouseCursorGrabbed(true);
            P::Window().setMouseCursorVisible(false);
            P::Player().setGrabbed(true);
        }
    } else if (event.type == sf::Event::MouseMoved && P::Window().hasFocus()) {
        P::Player().computeMatricesMouse(P::Window());
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (rayCastResult.isFound) {
                P::World().oneBlock(WorldTaskType::SingleBlockRemove, rayCastResult.iend);
            }
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            if (rayCastResult.isFound) {
                P::World().oneBlock(WorldTaskType::SingleBlockPlace, rayCastResult.iend + (sf::Vector3<int64_t>) rayCastResult.norm);
            }
        }
    }
}

void Client::update() {
    float deltaTime = deltaTimeClock.restart().asSeconds();
    if (P::Window().hasFocus())
        P::Player().computePlayerPosKeyboard(P::Window(), deltaTime);
    rayCastResult = P::World().rayCast(P::Player().getPlayerPos(), P::Player().getDirection(), 100.0f);
//    if (rayCastResult.isFound) {
//        std::cout << "Looking at: X:" << rayCastResult.iend.x << " Y:" << rayCastResult.iend.y << "Z:" << rayCastResult.iend.z << std::endl;
//    }
}
void Client::thread_main() {
//    for (int x = 0; x < 100; x++) {
//        for (int y = 0; y < 100; y++) {
//            for (int z = 0; z < 100; z++) {
//                P::World().oneBlock(WorldTaskType::SingleBlockPlace, sf::Vector3<int64_t>(x, y, z));
//            }
//        }
//    }
    P::World().oneBlock(WorldTaskType::SingleBlockPlace, sf::Vector3<int64_t>(0,0,0));
    while (on) {
        sf::Event event{};
        while (P::Window().pollEvent(event)) {
            handleEvent(event);
        }
        update();
    }
}


#pragma clang diagnostic pop