#include <SFML/Window/Event.hpp>
#include "Application/Client.hpp"
int main() {
    Client application;
    while (application.isOpen()) {
        sf::Event event{};
        while (application.pollEvent(event))
            application.handleEvent(event);
        application.update();
        application.draw();
    }
}
