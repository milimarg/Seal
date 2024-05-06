#ifndef SEAL_CARTRIDGE_HPP
    #define SEAL_CARTRIDGE_HPP
    #include <cstdint>
    #include <memory>
    #include <vector>
    #include <fstream>
    #include "Mapper/Mapper000.hpp"

class Cartridge {
public:
    Cartridge(const std::string &filename);
    ~Cartridge();

    bool cpuRead(uint16_t addr, uint8_t &data);
    bool cpuWrite(uint16_t addr, uint8_t data);

    bool ppuRead(uint16_t addr, uint8_t &data);
    bool ppuWrite(uint16_t addr, uint8_t data);

private:
    std::vector<uint8_t> PRGMemory;
    std::vector<uint8_t> CHRMemory;
    uint8_t mapperId = 0;
    uint8_t PRGBanks = 0;
    uint8_t CHRBanks = 0;
    std::shared_ptr<Mapper> mapper;
};

#endif //SEAL_CARTRIDGE_HPP
