#include <iostream>
#include <sstream>
#include "../includes/Emulator.hpp"

int main(int argc, char **argv)
{
    sf::Event event;
    sf::Clock clock;
    float time = 0;
    float current = 0;

    if (argc != 2) {
        std::cerr << "Command should be: ./seal <rom filepath>" << std::endl;
        return 1;
    }
    Emulator &emulator = Emulator::getInstance();

    emulator.setWindow(std::make_shared<sf::RenderWindow>(sf::VideoMode{1920, 1080}, "Seal"));
    emulator.setRomFilepath(std::string(argv[1]));
    if (!emulator.init()) {
        std::cerr << "Emulator failed to init..." << std::endl;
    }

    std::shared_ptr<sf::RenderWindow> window = emulator.getWindow();
    while (window->isOpen()) {
        window->clear();
        while (window->pollEvent(event))
            if (event.type == sf::Event::Closed)
                window->close();
        current = clock.getElapsedTime().asMilliseconds();
        if (current - time > 16.67f) {
            time = current;
            emulator.update();
        }
        emulator.render();
        window->display();
    }
	return 0;
}
