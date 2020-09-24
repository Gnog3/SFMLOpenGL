#include <SFML/Graphics.hpp>
#include "Application/World/World.hpp"
#include "Application/Engine/Engine.hpp"
#include "Application/Player/Player.hpp"
#include "Application/GlobalRef.hpp"
#include "Application/DestructionTimer.hpp"
#include "Application/Client.hpp"

void a() {

};
int main() {
    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 0;
    contextSettings.majorVersion = 3;
    contextSettings.minorVersion = 3;
    contextSettings.depthBits = 24;
    contextSettings.attributeFlags = sf::ContextSettings::Core;
    sf::RenderWindow window(sf::VideoMode(1600, 900), "OpenGL", sf::Style::Default, contextSettings);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW init failed" << std::endl;
        std::exit(-1);
    }
    window.setFramerateLimit(75);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    window.setMouseCursorGrabbed(true);
    window.setMouseCursorVisible(false);
    window.setActive(false);
    P::setWindow(&window);
    Player player;
    P::setPlayer(&player);
    Engine engine;
    P::setEngine(&engine);
    World world;
    P::setWorld(&world);
    Client client;
    P::setClient(&client);
    engine.start_thread();
    world.start_thread();
    engine.wait_init();
    client.thread_main();
    std::cout << "Stopping app..." << std::endl;
    engine.require_stop();
    world.require_stop();
    engine.wait_stop();
    world.wait_stop();
    window.setActive(true);
}
