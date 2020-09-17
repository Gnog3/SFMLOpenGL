#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

#include "Client.hpp"

Client::Client() {
    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 0;
    contextSettings.majorVersion = 3;
    contextSettings.minorVersion = 3;
    contextSettings.depthBits = 24;
    contextSettings.attributeFlags = sf::ContextSettings::Core;
    window.create(sf::VideoMode(1600, 900), "OpenGL", sf::Style::Default, contextSettings);
    contextSettings = window.getSettings();
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
    engine.emplace(window, player);
    world.emplace(engine.value());
    engine->start_thread();
    world->start_thread();

//    std::cout << "Creating world... ";
//    Timer timer;
//    for (int x = 0; x < 100; x++) {
//        for (int y = 0; y < 100; y++) {
//            for (int z = 0; z < 100; z++) {
//                world->placeBlock(1, sf::Vector3<int64_t>(x,y,z));
//            }
//        }
//    }
//    world->placeBlock(1, sf::Vector3<int64_t>(0,0,0));
//    std::cout << "It took " << timer.getMilliseconds() << "ms" << std::endl;
//
//    std::cout << "Calculating vertices... ";
//    timer.restart();
//    for (auto& chunk : world->chunkMap) {
//        Chunk& c = chunk.second;
//        c.calculateVertices(world->chunkMap);
//    }
//    std::cout << "It took " << timer.getMilliseconds() << "ms" << std::endl;
//
//    std::cout << "Sending vertices... ";
//    timer.restart();
//    for (auto& chunk : world->chunkMap) {
//        Chunk& c = chunk.second;
//        c.sendVertices();
//    }
//    std::cout << "It took " << timer.getMilliseconds() << "ms" << std::endl;
}

Client::~Client() {
    engine->requireStop();
    world->requireStop();
    std::cout << "Waiting for engine..." << std::endl;
    engine->waitStop();
    std::cout << "Waiting for world..." << std::endl;
    world->waitStop();
    window.setActive(true);
}

bool Client::isOpen() {
    return !requireClose;
}

void Client::wait_for_engine() {
    engine->waitInit();
}

bool Client::pollEvent(sf::Event& event) {
    return window.pollEvent(event);
}

void Client::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            requireClose = true;
        } else if (event.key.code == sf::Keyboard::Q) {
            window.setMouseCursorGrabbed(false);
            window.setMouseCursorVisible(true);
            player.setGrabbed(false);
        } else if (event.key.code == sf::Keyboard::E) {
            window.setMouseCursorGrabbed(true);
            window.setMouseCursorVisible(false);
            player.setGrabbed(true);
        }
    } else if (event.type == sf::Event::MouseMoved && window.hasFocus()) {
        player.computeMatricesMouse(window);
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (rayCastResult.isFound) {
                world->oneBlock(WorldTaskType::SingleBlockRemove, rayCastResult.iend);
            }
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            if (rayCastResult.isFound) {
                world->oneBlock(WorldTaskType::SingleBlockPlace, rayCastResult.iend + (sf::Vector3<int64_t>) rayCastResult.norm);
            }
        }
    }
}
void Client::update() {
    deltaTime = deltaTimeClock.restart().asSeconds();
    if (window.hasFocus())
        player.computePlayerPosKeyboard(window, deltaTime);
    rayCastResult = world->rayCast(player.getPlayerPos(), player.getDirection(), 100.0f);
//    if (rayCastResult.isFound) {
//        std::cout << "Looking at: X:" << rayCastResult.iend.x << " Y:" << rayCastResult.iend.y << "Z:" << rayCastResult.iend.z << std::endl;
//    }
}
void Client::after_init() {
    world->oneBlock(WorldTaskType::SingleBlockPlace, sf::Vector3<int64_t>(-1,-1,-1));
}


#pragma clang diagnostic pop