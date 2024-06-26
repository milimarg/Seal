/*
** EPITECH PROJECT, 2024
** Seal
** File description:
** Emulator.hpp
*/

#ifndef SEAL_EMULATOR_HPP
    #define SEAL_EMULATOR_HPP
    #include <unordered_map>
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>
    #include "Bus.hpp"
    #include "Byte.hpp"

class Emulator {
public:
    static Emulator &getInstance();
    bool init();

    void setWindow(std::shared_ptr<sf::RenderWindow> window);
    void setRomFilepath(const std::string &filepath);
    std::shared_ptr<sf::RenderWindow> getWindow();

    void drawImage(const sf::Image &image,
                   const sf::Vector2f &position = sf::Vector2f(0, 0),
                   const sf::Vector2f &scale = sf::Vector2f(1, 1));
    void drawRectangle(const sf::IntRect &rect,
                       const sf::Color &color,
                       const sf::Color &borderColor);
    void update();
    void render();

    Bus nes;
    std::shared_ptr<Cartridge> _cartridge;
    bool _runningEmulation = false;
    float fResidualTime = 0.0f;
    uint8_t _selectedPalette = 0x00;
    std::map<uint16_t, std::string> _asm;
    std::string _romFilepath;
    std::shared_ptr<sf::RenderWindow> _window;
    sf::Text _text;
    sf::Font _font;

private:
    Emulator();
    ~Emulator();
    void updateControllers();
    void updateKeys();
    sf::Color getCpuFlagStatusColor(const Cpu::FLAGS6502 flag);
    void drawCpu(const sf::Vector2i &position);
    void drawInstructions(const sf::Vector2i &position, const int linesNumber);

    std::unordered_map<std::string, bool> _antiSpams;
    std::array<std::pair<std::string, Cpu::FLAGS6502>, 7> _cpuFlags;
    double _timeLoop;
    sf::VertexArray _vertexArray;
};

#endif //SEAL_EMULATOR_HPP
