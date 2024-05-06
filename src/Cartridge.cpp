#include "../includes/Cartridge.hpp"

Cartridge::Cartridge(const std::string &filename)
{
    struct header
    {
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

    std::ifstream stream;
    stream.open(filename, std::ifstream::binary);
    if (stream.is_open()) {
        stream.read((char *)&header, sizeof(header));

        if (header.mapper1 & 0x04)
            stream.seekg(512, std::ios_base::cur);

        mapperId = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);

        uint8_t fileType = 1;

        switch (fileType) {
            case 0:
                break;
            case 1:
                PRGBanks = header.prg_rom_chunks;
                PRGMemory.resize(PRGBanks * 16384);
                stream.read((char *)PRGMemory.data(), PRGMemory.size());

                CHRBanks = header.chr_rom_chunks;
                CHRMemory.resize(CHRBanks * 8192);
                stream.read((char *)CHRMemory.data(), CHRMemory.size());
            case 2:
                break;
        }

        switch (mapperId) {
            case 0:
                mapper = std::make_shared<Mapper_000>(PRGBanks, CHRBanks);
                break;
        }

        stream.close();
    }
}

Cartridge::~Cartridge()
{

}

bool Cartridge::cpuRead(uint16_t addr, uint8_t &data)
{
    uint32_t mapped_addr = 0;

    if (mapper->cpuMapRead(addr, mapped_addr)) {
        data = PRGMemory[mapped_addr];
        return true;
    }
    return false;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t data)
{
    (void)addr;
    (void)data;
    return false;
}

bool Cartridge::ppuRead(uint16_t addr, uint8_t &data)
{
    (void)addr;
    (void)data;
    return false;
}

bool Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;

    if (mapper->cpuMapRead(addr, mapped_addr)) {
        CHRMemory[mapped_addr] = data;
        return true;
    }
    return false;
}
