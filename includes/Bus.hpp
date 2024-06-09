#ifndef SEAL_BUS_HPP
    #define SEAL_BUS_HPP
    #include <cstdint>
    #include <array>
    #include "../includes/Cpu.hpp"
    #include "../includes/Ppu.hpp"
    #include "../includes/Cartridge.hpp"

class Bus {
public:
    Bus();
    ~Bus();

public:
    Cpu cpu;
    Ppu ppu;
    std::shared_ptr<Cartridge> _cartridge;
    uint8_t cpuRam[2048];
    uint8_t controller[2];

public:
    void    cpuWrite(uint16_t addr, uint8_t data);
    uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);

private:
    uint32_t systemClockCounter = 0;
    uint8_t controller_state[2];
    uint8_t dma_page = 0x00;
    uint8_t dma_addr = 0x00;
    uint8_t dma_data = 0x00;
    bool dma_dummy = true;
    bool dma_transfer = false;

public:
    void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
    void reset();
    void clock();
};

#endif //SEAL_BUS_HPP
