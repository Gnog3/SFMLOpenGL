#include <SFML/Window/Event.hpp>
#include <chrono>
#include "Application/Client.hpp"
#include "Application/DestructionTimer.hpp"
int main() {
    DestructionTimer<Client> application("Client");
    std::cout << "Waiting for engine init..." << std::endl;
    application->wait_for_engine();
    std::cout << "Engine wait complete." << std::endl;
    application->after_init();
    while (application->isOpen()) {
        sf::Event event{};
        while (application->pollEvent(event)) {
            application->handleEvent(event);
        }
        application->update();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
