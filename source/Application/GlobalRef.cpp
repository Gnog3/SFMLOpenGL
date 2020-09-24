#include "GlobalRef.hpp"

Client* P::client;
World* P::world;
Engine* P::engine;
Player* P::player;
sf::RenderWindow* P::window;

void P::setClient(class Client* a_client) {
    client = a_client;
}
void P::setWorld(class World* a_world) {
    world = a_world;
}
void P::setEngine(class Engine* a_engine) {
    engine = a_engine;
}
void P::setPlayer(class Player* a_player) {
    player = a_player;
}
void P::setWindow(class sf::RenderWindow* a_window) {
    window = a_window;
}
Client& P::Client() {
    return *client;
}
World& P::World() {
    return *world;
}
Engine& P::Engine() {
    return *engine;
}
Player& P::Player() {
    return *player;
}
sf::RenderWindow& P::Window() {
    return *window;
}
