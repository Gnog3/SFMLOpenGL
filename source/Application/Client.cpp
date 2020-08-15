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
    WRef::setWorld(world.get());

//    world->placeThing(Thing::wool_white, sf::Vector3i(-10, -10, -10));
//    world->placeThing(Thing::wool_white, sf::Vector3i(0, 0, 0));
//    world->placeThing(Thing::wool_white, sf::Vector3i(1, 1, 0));
//    world->placeThing(Thing::wool_white, sf::Vector3i(2, 2, 0));
//    world->placeThing(Thing::wool_white, sf::Vector3i(3, 3, 0));
//    world->placeThing(Thing::wool_white, sf::Vector3i(4, 4, 0));
#ifdef DEBUG
    uint32_t _amount_ = 0;
#endif
    std::cout << "Putting blocks..." << std::endl;
    sf::Clock clock;
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            for (int z = 0; z < 100; z++) {
                
                world->placeThing(Thing::wool_white,
                                  sf::Vector3i(x * 2, y * 2, z * 2));
#ifdef DEBUG
                _amount_++;
                if (_amount_ % 1000 == 0)
                    std::cout << _amount_ / 1000000.0f * 100.0f << "%" << std::endl;
#endif
            }
        }
    }
    world->placeThing(Thing::wool_white, sf::Vector3i(-10, -10, -10));
    std::cout << "It took " << clock.getElapsedTime().asSeconds() << "s" << std::endl;
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