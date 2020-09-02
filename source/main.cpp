#include <SFML/Window/Event.hpp>
#include "Application/Client.hpp"
#include "Application/DestructionTimer.hpp"
int main() {
    DestructionTimer<Client> application("Client");
    while (application->isOpen()) {
        sf::Event event{};
        while (application->pollEvent(event))
            application->handleEvent(event);
        application->update();
        application->draw();
    }
}
