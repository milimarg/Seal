#include "../includes/Bus.hpp"

Bus::Bus()
{
    for (auto &byte : cpuRam)
        byte = 0x00;
    cpu.connectBus(this);
}

Bus::~Bus() {}

void Bus::cpuWrite(uint16_t addr, uint8_t data)
{
    if (_cartridge->cpuWrite(addr, data)) {

    }
    else if (IS_IN_CPU_RAM(addr))
        cpuRam[addr & _2K_HEXA] = data;
    else if (addr >= 0x2000 && addr <= 0x3FFF)
        ppu.cpuWrite(addr & 0x0007, data);
}

uint8_t Bus::cpuRead(uint16_t addr, bool readOnly)
{
    uint8_t data = 0x00;

    if (_cartridge->cpuRead(addr, data)) {

    } else if (IS_IN_CPU_RAM(addr))
        data = cpuRam[addr & _2K_HEXA];
    else if (addr >= 0x2000 && addr <= 0x3FFF)
        data = ppu.cpuRead(addr & 0x0007, readOnly);
    return data;
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge> &cartridge)
{
    _cartridge = cartridge;
    ppu.connectCartridge(_cartridge);
}

void Bus::reset()
{
    cpu.reset();
    systemClockCounter = 0;
}

void Bus::clock()
{
    ppu.clock();
    if (systemClockCounter % 3 == 0) // Because CPU is 3x slower than PPU
        cpu.clock();
    systemClockCounter += 1;
}
