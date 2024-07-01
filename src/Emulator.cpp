/*
** EPITECH PROJECT, 2024
** Seal
** File description:
** Emulator.cpp
*/

#include "../includes/Emulator.hpp"

Emulator::Emulator()
    : _antiSpams({
        {"SPACE", false},
        {"F", false}
    }),
    _cpuFlags({
        {"N", Cpu::FLAGS6502::N}, // is negative?
        {"V", Cpu::FLAGS6502::V}, // has overflowed?
        {"B", Cpu::FLAGS6502::B}, // has broken?
        {"D", Cpu::FLAGS6502::D}, // is decimal?
        {"I", Cpu::FLAGS6502::I}, // has interrupted?
        {"Z", Cpu::FLAGS6502::Z}, // is zero?
        {"C", Cpu::FLAGS6502::C}  // has carry?
    }) {}

Emulator::~Emulator() {}

Emulator &Emulator::getInstance()
{
    static Emulator emulator;
    return emulator;
}

bool Emulator::init()
{
    if (!nes.insertCartridge(_romFilepath)) {
        std::cerr << "Nes failed to insert cartridge..." << std::endl;
        return false;
    }
    _asm = nes.cpu.disassemble(0x0000, 0xFFFF);
    _font.loadFromFile("./Roboto-Regular.ttf");
    _text.setCharacterSize(20);
    _text.setFont(_font);
    _vertexArray.setPrimitiveType(sf::Quads);
    nes.reset();
    return true;
}

void Emulator::setWindow(std::shared_ptr<sf::RenderWindow> window)
{
    _window = window;
}

void Emulator::setRomFilepath(const std::string &filepath)
{
    _romFilepath = filepath;
}

std::shared_ptr<sf::RenderWindow> Emulator::getWindow()
{
    return _window;
}

void Emulator::drawImage(const sf::Image &image,
                         const sf::Vector2f &position,
                         const sf::Vector2f &scale)
{
    for (unsigned int y = 0; y < image.getSize().y; ++y) {
        for (unsigned int x = 0; x < image.getSize().x; ++x) {
            _vertexArray.append(sf::Vertex(
                    {static_cast<float>(x) * scale.x, static_cast<float>(y) * scale.y},
                    image.getPixel(x, y)
            ));
            if (scale.x == 1.0f && scale.y == 1.0f)
                continue;
            _vertexArray.append(sf::Vertex(
                    {static_cast<float>(x + 1) * scale.x, static_cast<float>(y) * scale.y},
                    image.getPixel(x, y)
            ));
            _vertexArray.append(sf::Vertex(
                    {static_cast<float>(x + 1) * scale.x, static_cast<float>(y + 1) * scale.y},
                    image.getPixel(x, y)
            ));
            _vertexArray.append(sf::Vertex(
                    {static_cast<float>(x) * scale.x, static_cast<float>(y + 1) * scale.y},
                    image.getPixel(x, y)
            ));
        }
    }
}

void Emulator::update()
{
    updateControllers();
    updateKeys();

    if (_runningEmulation) {
        do {
            nes.clock();
        } while (!nes.ppu.frame_complete);
        nes.ppu.frame_complete = false;
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !_antiSpams["F"]) {
        _antiSpams["F"] = true;
        do {
            nes.clock();
        } while (!nes.ppu.frame_complete);
        do {
            nes.clock();
        } while (!nes.cpu.complete());
        nes.ppu.frame_complete = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F) && _antiSpams["F"])
        _antiSpams["F"] = false;
}

void Emulator::render()
{
    _vertexArray.clear();
    drawCpu({1300, 10});
    drawInstructions({1600, 40}, 22);
    drawImage(nes.ppu.GetScreen(), {0, 0}, {4, 4});
    _window->draw(_vertexArray);
}

void Emulator::updateControllers()
{
    nes.controller[0] = 0x00;
    nes.controller[0] |= sf::Keyboard::isKeyPressed(sf::Keyboard::X) ? 0x80 : 0x00;
    nes.controller[0] |= sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ? 0x40 : 0x00;
    nes.controller[0] |= sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? 0x20 : 0x00;
    nes.controller[0] |= sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? 0x10 : 0x00;
    nes.controller[0] |= sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? 0x08 : 0x00;
    nes.controller[0] |= sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? 0x04 : 0x00;
    nes.controller[0] |= sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? 0x02 : 0x00;
    nes.controller[0] |= sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? 0x01 : 0x00;
}

void Emulator::updateKeys()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !_antiSpams["SPACE"]) {
        _runningEmulation = !_runningEmulation;
        _antiSpams["SPACE"] = true;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _antiSpams["SPACE"])
        _antiSpams["SPACE"] = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        nes.reset();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        (++_selectedPalette) &= 0x07;
}

sf::Color Emulator::getCpuFlagStatusColor(const Cpu::FLAGS6502 flag)
{
    return nes.cpu.status & static_cast<uint8_t>(flag) ? sf::Color::Green : sf::Color::Red;
}

void Emulator::drawCpu(const sf::Vector2i &position)
{
    size_t index = 0;

    for (auto &[name, flag] : _cpuFlags) {
        _text.setPosition(position.x + (index * 20), position.y);
        _text.setString(name);
        _text.setFillColor(getCpuFlagStatusColor(flag));
        _window->draw(_text);
        ++index;
    }
    index = 0;
    _text.setFillColor(sf::Color::White);
    const std::array<std::pair<std::string, uint8_t>, 4> _cpuRegisters = {
            std::make_pair("Register A", nes.cpu.a),
            std::make_pair("Register X", nes.cpu.x),
            std::make_pair("Register Y", nes.cpu.y),
            std::make_pair("Stack Pointer", nes.cpu.stackPtr)
    };
    for (auto &[name, value] : _cpuRegisters) {
        _text.setPosition(position.x, position.y + 30 + (index * 30));
        _text.setString(name + ": $" + Byte::hex(value, 4));
        _window->draw(_text);
        ++index;
    }
}

void Emulator::drawInstructions(const sf::Vector2i &position,
                                const int linesNumber)
{
    auto it = _asm.find(nes.cpu.pc);
    int nLineY = (linesNumber >> 1) * 10 + position.y;

    if (it != _asm.end()) {
        _text.setPosition(position.x, nLineY);
        _text.setString(it->second);
        _text.setFillColor(sf::Color::Magenta);
        _window->draw(_text);
        while (nLineY < (linesNumber * 10) + position.y) {
            nLineY += 25;
            if (++it != _asm.end()) {
                _text.setPosition(position.x, nLineY);
                _text.setString(it->second);
                _text.setFillColor(sf::Color::White);
                _window->draw(_text);
            }
        }
    }
    it = _asm.find(nes.cpu.pc);
    nLineY = (linesNumber >> 1) * 10 + position.y;
    if (it != _asm.end()) {
        while (nLineY > position.y) {
            nLineY -= 25;
            if (--it != _asm.end()) {
                _text.setPosition(position.x, nLineY);
                _text.setString(it->second);
                _text.setFillColor(sf::Color::White);
                _window->draw(_text);
            }
        }
    }
}
