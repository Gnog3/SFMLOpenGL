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
#include "Thready.hpp"
// Requires nothing for construction
// Requires window, world, player for thread
class Client {
    private:
        sf::Clock deltaTimeClock;
        RayCastResult rayCastResult;
        
        void handleEvent(sf::Event& event);
        void update();
        bool on = true;
    public:
        void thread_main();
};

#endif //SFMLOPENGL_CLIENT_HPP
