#include "../../includes/Mapper/Mapper.hpp"

Mapper::Mapper(uint8_t prgBanks, uint8_t chrBanks)
    : _PRGBanks(prgBanks), _CHRBanks(chrBanks) {}

Mapper::~Mapper() {}
