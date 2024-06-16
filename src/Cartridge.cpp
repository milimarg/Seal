#include <iostream>
#include "../includes/Cartridge.hpp"

Cartridge::Cartridge(const std::string& filepath)
{
	struct sHeader {
		char name[4];
		uint8_t prg_rom_chunks;
		uint8_t chr_rom_chunks;
		uint8_t mapper1;
		uint8_t mapper2;
		uint8_t prg_ram_size;
		uint8_t tv_system1;
		uint8_t tv_system2;
		char unused[5];
	} header;

	_imageValid = false;

	std::ifstream ifs;
	ifs.open(filepath, std::ifstream::binary);

	if (ifs.is_open()) {
		ifs.read((char*)&header, sizeof(sHeader));

		if (header.mapper1 & 0x04)
			ifs.seekg(512, std::ios_base::cur);

		nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
		mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;

		uint8_t nFileType = 1;

		if (nFileType == 1) {
			PRGBanks = header.prg_rom_chunks;
			vPRGMemory.resize(PRGBanks * 16384);
			ifs.read((char*)vPRGMemory.data(), vPRGMemory.size());

			CHRBanks = header.chr_rom_chunks;
			if (CHRBanks == 0) {
				vCHRMemory.resize(8192);
			} else {
				vCHRMemory.resize(CHRBanks * 8192);
			}
			ifs.read((char*)vCHRMemory.data(), vCHRMemory.size());
		}
		switch (nMapperID) {
		    case 0:
                _mapper = Factory::createElement<Mapper_000>(PRGBanks, CHRBanks);
                break;
            default:
                break;
		}
		_imageValid = true;
		ifs.close();
	}
}

Cartridge::~Cartridge() {}

bool Cartridge::imageValid()
{
	return _imageValid;
}

bool Cartridge::cpuRead(uint16_t addr, uint8_t &data)
{
	uint32_t mapped_addr = 0;
	if (_mapper->cpuMapRead(addr, mapped_addr)) {
		data = vPRGMemory[mapped_addr];
		return true;
	}
    return false;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t data)
{
	uint32_t mapped_addr = 0;
	if (_mapper->cpuMapWrite(addr, mapped_addr, data)) {
		vPRGMemory[mapped_addr] = data;
		return true;
	}
	return false;
}

bool Cartridge::ppuRead(uint16_t addr, uint8_t & data)
{
	uint32_t mapped_addr = 0;

	if (_mapper->ppuMapRead(addr, mapped_addr)) {
		data = vCHRMemory[mapped_addr];
		return true;
	}
	return false;
}

bool Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{
	uint32_t mapped_addr = 0;

	if (_mapper->ppuMapWrite(addr, mapped_addr)) {
		vCHRMemory[mapped_addr] = data;
		return true;
	}
	return false;
}

void Cartridge::reset()
{
	if (_mapper != nullptr)
		_mapper->reset();
}
