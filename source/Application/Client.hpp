#ifndef SFMLOPENGL_CLIENT_HPP

#define SFMLOPENGL_CLIENT_HPP

#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include "Player/Player.hpp"
#include "World/World.hpp"
#include "Engine/Engine.hpp"
#include "World/Block/Block.hpp"
#include "Timer/Timer.hpp"

class Client {
    private:
        Player player;
        sf::Clock deltaTimeClock;
        sf::RenderWindow window;
        std::optional<Engine> engine;
        std::optional<World> world;
        RayCastResult rayCastResult;
        bool requireClose = false;
        float deltaTime = 0;
        
    public:
        Client();
        ~Client();
        bool isOpen();
        void wait_for_engine();
        bool pollEvent(sf::Event& event);
        void handleEvent(sf::Event& event);
        void update();
        void after_init();
};


#endif //SFMLOPENGL_CLIENT_HPP
