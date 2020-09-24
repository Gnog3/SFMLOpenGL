#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class World;

class Engine;

class Client;

class Player;

class P {
    public:
        static Client* client;
        static World* world;
        static Engine* engine;
        static Player* player;
        static sf::RenderWindow* window;
    public:
        static void setClient(class Client* a_client);
        static void setWorld(class World* a_world);
        static void setEngine(class Engine* a_engine);
        static void setPlayer(class Player* a_player);
        static void setWindow(class sf::RenderWindow* a_window);
        static Client& Client();
        static World& World();
        static Engine& Engine();
        static Player& Player();
        static sf::RenderWindow& Window();
};
