#ifndef SEAL_CARTRIDGE_HPP
    #define SEAL_CARTRIDGE_HPP
    #include <cstdint>
    #include <string>
    #include <fstream>
    #include <vector>
    #include <memory>
    #include "Mapper/Mapper_000.hpp"
    #include "Factory.hpp"

class Cartridge {
public:
    Cartridge() {}
    Cartridge(const std::string& filepath);
    ~Cartridge();

public:
    bool imageValid();

    enum MIRROR {
        HORIZONTAL,
        VERTICAL,
        ONESCREEN_LO,
        ONESCREEN_HI,
    } mirror = HORIZONTAL;

private:
    bool _imageValid = false;

    uint8_t nMapperID = 0;
    uint8_t PRGBanks = 0;
    uint8_t CHRBanks = 0;

    std::vector<uint8_t> vPRGMemory;
    std::vector<uint8_t> vCHRMemory;

    std::shared_ptr<Mapper> _mapper;

public:
    bool cpuRead(uint16_t addr, uint8_t &data);
    bool cpuWrite(uint16_t addr, uint8_t data);
    bool ppuRead(uint16_t addr, uint8_t &data);
    bool ppuWrite(uint16_t addr, uint8_t data);

    void reset();
};

#endif //SEAL_CARTRIDGE_HPP
