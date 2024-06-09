#include "../../includes/Mapper/Mapper_000.hpp"

Mapper_000::Mapper_000(uint8_t prgBanks, uint8_t chrBanks) :
    Mapper(prgBanks, chrBanks) {}

Mapper_000::~Mapper_000() {}

void Mapper_000::reset() {}

bool Mapper_000::cpuMapRead(uint16_t address, uint32_t &mapped_addr)
{
	if (address >= 0x8000 && address <= 0xFFFF) {
		mapped_addr = address & (_PrgBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}
	return false;
}

bool Mapper_000::cpuMapWrite(uint16_t address, uint32_t &mapped_addr, uint8_t data)
{
	if (address >= 0x8000 && address <= 0xFFFF) {
		mapped_addr = address & (_PrgBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}
	return false;
}

bool Mapper_000::ppuMapRead(uint16_t address, uint32_t &mapped_addr)
{
	if (address >= 0x0000 && address <= 0x1FFF) {
		mapped_addr = address;
		return true;
	}
	return false;
}

bool Mapper_000::ppuMapWrite(uint16_t address, uint32_t &mapped_addr)
{
	if (address >= 0x0000 && address <= 0x1FFF && _ChrBanks == 0) {
        mapped_addr = address;
        return true;
	}
	return false;
}
