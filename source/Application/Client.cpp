#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"


#include "Client.hpp"

Client::Client() {
    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 4;
    contextSettings.majorVersion = 3;
    contextSettings.minorVersion = 3;
    contextSettings.depthBits = 24;
    contextSettings.attributeFlags = sf::ContextSettings::Core;
    window.create(sf::VideoMode(1600, 900), "OpenGL", sf::Style::Default, contextSettings);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW init failed" << std::endl;
        std::exit(-1);
    }
    //window.setFramerateLimit(75);
    //glEnable(GL_CULL_FACE);
    window.setMouseCursorGrabbed(true);
    window.setMouseCursorVisible(false);
    world = std::make_unique<World>();
}

Client::~Client() {

}

bool Client::isOpen() {
    return window.isOpen();
}

bool Client::pollEvent(sf::Event& event) {
    return window.pollEvent(event);
}

void Client::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        window.close();
    if (event.type == sf::Event::MouseMoved && window.hasFocus())
        player.computeMatricesMouse(window);
}

void Client::update() {
    deltaTime = deltaTimeClock.restart().asSeconds();
    if (window.hasFocus())
        player.computePlayerPosKeyboard(window, deltaTime);
}

void Client::draw() {
    sf::Clock drawClock;
    glClearColor(0.0f, 0.6f, 0.6f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    world->draw(player);
    window.display();
    std::cout << 1 / drawClock.restart().asSeconds() << std::endl;
}


#pragma clang diagnostic pop