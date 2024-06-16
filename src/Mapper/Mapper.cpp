#include "../../includes/Mapper/Mapper.hpp"

Mapper::Mapper(uint8_t prgBanks, uint8_t chrBanks)
{
	_PrgBanks = prgBanks;
	_ChrBanks = chrBanks;
}

Mapper::~Mapper() {}

void Mapper::reset() {}
