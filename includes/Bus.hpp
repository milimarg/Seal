#ifndef SEAL_BUS_HPP
    #define SEAL_BUS_HPP
    #include <cstdint>
    #include <array>
    #include "Core.hpp"
    #include "Ppu.hpp"
    #include "Cartridge.hpp"

    #define IS_IN_CPU_RAM(a) a >= 0x0000 && a <= 0x1FFF
    #define _2K_HEXA 0x07FF

class Bus {
public:
    Bus();
    ~Bus();

    Core cpu;
    PPU ppu;
    std::array<uint8_t, 2048> cpuRam;
    std::shared_ptr<Cartridge> _cartridge;

    void cpuWrite(uint16_t addr, uint8_t data);
    uint8_t cpuRead(uint16_t addr, bool readOnly = false);

    void insertCartridge(const std::shared_ptr<Cartridge> &cartridge);
    void reset();
    void clock();

private:
    uint32_t systemClockCounter = 0;
};

#endif //SEAL_BUS_HPP
