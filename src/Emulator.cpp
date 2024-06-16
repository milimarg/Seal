/*
** EPITECH PROJECT, 2024
** Seal
** File description:
** Emulator.cpp
*/

#include "../includes/Emulator.hpp"

Emulator::Emulator(sf::RenderWindow &window, const std::string &romFilepath)
    : _window(window),
    _romFilepath(romFilepath),
    _antiSpams({
        {"SPACE", false},
        {"F", false}
    })
{
    if (!nes.insertCartridge(_romFilepath))
        return;
    _asm = nes.cpu.disassemble(0x0000, 0xFFFF);
    _font.loadFromFile("./Roboto-Regular.ttf");
    _text.setCharacterSize(20);
    _text.setFont(_font);
    nes.reset();
}

bool Emulator::drawImage(const sf::Image &image,
                         const sf::Vector2f &position,
                         const sf::Vector2f &scale)
{
    sf::Sprite sprite;
    sf::Texture texture;

    if (image.getSize().x == 0 || image.getSize().y == 0)
        return false;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setScale(scale);
    _window.draw(sprite);
    return true;
}

void Emulator::update(double fElapsedTime)
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
    DrawCpu(516, 2);
    drawInstructions({1600, 40}, 22);
    drawImage(nes.ppu.GetPatternTable(0, _selectedPalette), {516, 348});
    drawImage(nes.ppu.GetPatternTable(1, _selectedPalette), {648, 348});
    drawImage(nes.ppu.GetScreen(), {0, 0}, {4, 4});
}

/* ---------- PRIVATE ---------- */

void Emulator::updateControllers()
{
    nes.controller[0] = 0x00;
    nes.controller[0] |=
            sf::Keyboard::isKeyPressed(sf::Keyboard::X)
            ? 0x80 : 0x00;
    nes.controller[0] |=
            sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
            ? 0x40 : 0x00;
    nes.controller[0] |=
            sf::Keyboard::isKeyPressed(sf::Keyboard::A)
            ? 0x20 : 0x00;
    nes.controller[0] |=
            sf::Keyboard::isKeyPressed(sf::Keyboard::S)
            ? 0x10 : 0x00;
    nes.controller[0] |=
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            ? 0x08 : 0x00;
    nes.controller[0] |=
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
            ? 0x04 : 0x00;
    nes.controller[0] |=
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
            ? 0x02 : 0x00;
    nes.controller[0] |=
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
            ? 0x01 : 0x00;
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

std::string Emulator::hex(uint32_t n, uint8_t d)
{
    std::string s(d, '0');

    for (int i = d - 1; i >= 0; i--, n >>= 4)
        s[i] = "0123456789ABCDEF"[n & 0xF];
    return s;
}

void Emulator::DrawRam(int x, int y, uint16_t nAddr, int nRows, int nColumns)
{
    int nRamX = x, nRamY = y;

    for (int row = 0; row < nRows; row++) {
        std::string sOffset = "$" + hex(nAddr, 4) + ":";
        for (int col = 0; col < nColumns; col++) {
            sOffset += " " + hex(nes.cpuRead(nAddr, true), 2);
            nAddr += 1;
        }
        //DrawString(nRamX, nRamY, sOffset);
        nRamY += 10;
    }
}

void Emulator::DrawCpu(int x, int y)
{
    //DrawString(x , y , "STATUS:", olc::WHITE);
    //DrawString(x  + 64, y, "N", nes.cpu.status & Cpu::N ? olc::GREEN : olc::RED);
    //DrawString(x  + 80, y , "V", nes.cpu.status & Cpu::V ? olc::GREEN : olc::RED);
    //DrawString(x  + 96, y , "-", nes.cpu.status & Cpu::U ? olc::GREEN : olc::RED);
    //DrawString(x  + 112, y , "B", nes.cpu.status & Cpu::B ? olc::GREEN : olc::RED);
    //DrawString(x  + 128, y , "D", nes.cpu.status & Cpu::D ? olc::GREEN : olc::RED);
    //DrawString(x  + 144, y , "I", nes.cpu.status & Cpu::I ? olc::GREEN : olc::RED);
    //DrawString(x  + 160, y , "Z", nes.cpu.status & Cpu::Z ? olc::GREEN : olc::RED);
    //DrawString(x  + 178, y , "C", nes.cpu.status & Cpu::C ? olc::GREEN : olc::RED);
    //DrawString(x , y + 10, "PC: $" + hex(nes.cpu.pc, 4));
    //DrawString(x , y + 20, "A: $" +  hex(nes.cpu.a, 2) + "  [" + std::to_string(nes.cpu.a) + "]");
    //DrawString(x , y + 30, "X: $" +  hex(nes.cpu.x, 2) + "  [" + std::to_string(nes.cpu.x) + "]");
    //DrawString(x , y + 40, "Y: $" +  hex(nes.cpu.y, 2) + "  [" + std::to_string(nes.cpu.y) + "]");
    //DrawString(x , y + 50, "Stack P: $" + hex(nes.cpu.stackPtr, 4));
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
        _window.draw(_text);
        while (nLineY < (linesNumber * 10) + position.y) {
            nLineY += 25;
            if (++it != _asm.end()) {
                _text.setPosition(position.x, nLineY);
                _text.setString(it->second);
                _text.setFillColor(sf::Color::White);
                _window.draw(_text);
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
                _window.draw(_text);
            }
        }
    }
}
