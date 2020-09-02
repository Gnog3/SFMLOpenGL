#ifndef SFMLOPENGL_CLIENT_HPP
#define SFMLOPENGL_CLIENT_HPP
#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>
#include "Player/Player.hpp"
#include "World/World.hpp"
#include "ogl.hpp"
#include "World/Block/Block.hpp"
#include "Timer/Timer.hpp"
#include "NotConstructed.hpp"
class Client {
    private:
        sf::RenderWindow window;
        Player player;
        sf::Clock deltaTimeClock;
        NotConstructed<World, true> world;
        RayCastResult rayCastResult;
        float deltaTime = 0;
    public:
        Client();
        ~Client();
        bool isOpen();
        bool pollEvent(sf::Event& event);
        void handleEvent(sf::Event& event);
        void update();
        void draw();
};


#endif //SFMLOPENGL_CLIENT_HPP
