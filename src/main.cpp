#include <iostream>
#include <sstream>
#include "../includes/Emulator.hpp"

int main(int argc, char **argv)
{
    sf::Event event;
    sf::RenderWindow window({1920, 1080}, "Seal");
    sf::Clock clock;
    float time = 0;
    float current = 0;

    if (argc != 2) {
        std::cerr << "Command should be ./seal <rom filepath>" << std::endl;
        return 1;
    }
    Emulator emulator(window, std::string(argv[1]));
    while (window.isOpen()) {
        window.clear();
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        current = clock.getElapsedTime().asMilliseconds();
        if (current - time > 16.67f) {
            time = current;
            emulator.update();
        }
        emulator.render();
        window.display();
    }
	return 0;
}
