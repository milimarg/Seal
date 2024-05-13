#ifndef SEAL_BUS_HPP
    #define SEAL_BUS_HPP
    #include <cstdint>
    #include <array>
    #include "../includes/Core.hpp"
    #include "../includes/Ppu.hpp"
    #include "../includes/Cartridge.hpp"

class Bus {
public:
    Bus();
    ~Bus();

public:
    Core cpu;
    Ppu ppu;
    std::shared_ptr<Cartridge> cart;
    uint8_t cpuRam[2048];
    uint8_t controller[2];

public:
    void    cpuWrite(uint16_t addr, uint8_t data);
    uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);

private:
    uint32_t systemClockCounter = 0;
    uint8_t controller_state[2];

public:
    void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
    void reset();
    void clock();
};

#endif //SEAL_BUS_HPP
