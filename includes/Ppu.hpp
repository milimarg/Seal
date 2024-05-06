#ifndef SEAL_PPU_HPP
    #define SEAL_PPU_HPP
    #include <cstdint>
    #include "Cartridge.hpp"

#include "../tests/olcPixelGameEngine.h"

class PPU {
public:
    PPU();
    ~PPU();

    uint8_t cpuRead(uint16_t addr, bool readOnly = false);
    void cpuWrite(uint16_t addr, uint8_t data);

    uint8_t ppuRead(uint16_t addr, bool readOnly = false);
    void ppuWrite(uint16_t addr, uint8_t data);

    void connectCartridge(const std::shared_ptr<Cartridge> &cartridge);
    void clock();

    olc::Sprite &getScreen();
    olc::Sprite &getNameTable(uint8_t i);
    olc::Sprite &getPatternTable(uint8_t i);
    bool frame_complete = false;

private:
    std::shared_ptr<Cartridge> _cartridge;
    uint8_t tblName[2][1024];
    uint8_t tblPalette[32];
    uint8_t tblPattern[2][4096]; // TODO: is in original console but will never be used

    olc::Pixel palScreen[0x40];
    olc::Sprite sprScreen = olc::Sprite(256, 240);
    olc::Sprite sprNameTable[2] = { olc::Sprite(256, 240), olc::Sprite(256, 240) };
    olc::Sprite sprPatternTable[2] = { olc::Sprite(128, 128), olc::Sprite(128, 128) };
    int16_t scanline = 0;
    int16_t cycle = 0;
};

#endif //SEAL_PPU_HPP
