#ifndef SEAL_PPU_HPP
    #define SEAL_PPU_HPP
    #include <cstdint>
    #include <memory>
    #include <cstring>
    #include <iostream>
    //#include "../tests/olcPixelGameEngine.hpp"
    #include <SFML/Graphics.hpp>
    #include "Cartridge.hpp"

class Ppu {
public:
    Ppu();
    ~Ppu();

private:
    uint8_t     tblName[2][1024];
    uint8_t     tblPattern[2][4096];
    uint8_t		tblPalette[32];

private:
    sf::Color _palScreen[0x40];
    sf::Image sprScreen;
    sf::Image sprPatternTable[2];

public:
    sf::Image& GetScreen();
    sf::Image& getPatternTable(uint8_t i, uint8_t palette);
    sf::Color GetColorFromPaletteRam(uint8_t palette, uint8_t pixel);
    bool frame_complete = false;

private:

    union {
        struct {
            uint8_t unused : 5;
            uint8_t sprite_overflow : 1;
            uint8_t sprite_zero_hit : 1;
            uint8_t vertical_blank : 1;
        };
        uint8_t reg;
    } status;


    union {
        struct {
            uint8_t grayscale : 1;
            uint8_t render_background_left : 1;
            uint8_t render_sprites_left : 1;
            uint8_t render_background : 1;
            uint8_t render_sprites : 1;
            uint8_t enhance_red : 1;
            uint8_t enhance_green : 1;
            uint8_t enhance_blue : 1;
        };
        uint8_t reg;
    } mask;

    union PPUCTRL {
        struct {
            uint8_t nametable_x : 1;
            uint8_t nametable_y : 1;
            uint8_t increment_mode : 1;
            uint8_t pattern_sprite : 1;
            uint8_t pattern_background : 1;
            uint8_t sprite_size : 1;
            uint8_t slave_mode : 1; // unused
            uint8_t enable_nmi : 1;
        };
        uint8_t reg;
    } control;

    union loopy_register {
        struct {
            uint16_t coarse_x : 5;
            uint16_t coarse_y : 5;
            uint16_t nametable_x : 1;
            uint16_t nametable_y : 1;
            uint16_t fine_y : 3;
            uint16_t unused : 1;
        };
        uint16_t reg = 0x0000;
    };

    loopy_register _vramAddr;
    loopy_register _tramAddr;

    uint8_t _fineX = 0x00;

    uint8_t _addressLatch = 0x00;
    uint8_t _ppuDataBuffer = 0x00;

    int16_t _scanline = 0;
    int16_t _cycle = 0;

    uint8_t _bgNextTileId     = 0x00;
    uint8_t _bgNextTileAttribute = 0x00;
    uint8_t _bgNextTileLst    = 0x00;
    uint8_t _bgNextTileMsb    = 0x00;
    uint16_t _bgShifterPatternLow = 0x0000;
    uint16_t _bgShifterPatternHigh = 0x0000;
    uint16_t _bgShifterAttributeLow  = 0x0000;
    uint16_t _bgShifterAttributeHigh  = 0x0000;

public:
    uint8_t cpuRead(uint16_t addr, bool rdonly = false);
    void cpuWrite(uint16_t addr, uint8_t  data);

    uint8_t ppuRead(uint16_t addr, bool rdonly = false);
    void ppuWrite(uint16_t addr, uint8_t data);

private:
    std::shared_ptr<Cartridge> cart;
    struct sObjectAttributeEntry
    {
        uint8_t y;
        uint8_t id;
        uint8_t attribute;
        uint8_t x;
    } OAM[64];

public:
    void connectCartridge(const std::shared_ptr<Cartridge> &cartridge);
    void clock();
    void reset();
    bool nmi = false;
    uint8_t *OAMPtr = (uint8_t *)&OAM[0];
    uint8_t oam_addr = 0x00;
    sObjectAttributeEntry spriteScanline[8];
    uint8_t sprite_count;
    uint8_t sprite_shifter_pattern_lo[8];
    uint8_t sprite_shifter_pattern_hi[8];
    bool spriteZeroHitPossible = false;
    bool spriteZeroBeingRendered = false;
};

#endif //SEAL_PPU_HPP
