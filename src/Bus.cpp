#include "../includes/Bus.hpp"

Bus::Bus()
{
    for (auto &byte : ram)
        byte = 0x00;
    cpu.connectBus(this);
}

Bus::~Bus() {}

void Bus::write(uint16_t addr, uint8_t data)
{
    if (IS_16_BIT(addr))
        ram[addr] = data;
}

uint8_t Bus::read(uint16_t addr, bool readOnly)
{
    if (IS_16_BIT(addr))
        return ram[addr];
    return 0;
}
