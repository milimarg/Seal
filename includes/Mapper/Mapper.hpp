#ifndef SEAL_MAPPER_HPP
    #define SEAL_MAPPER_HPP
    #include <cstdint>

class Mapper {
public:
    Mapper(uint8_t prgBanks, uint8_t chrBanks);
    ~Mapper();

public:
    virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
    virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data = 0) = 0;
    virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0;
    virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0;

    virtual void reset() = 0;

protected:
    uint8_t PRGBanks = 0;
    uint8_t CHRBanks = 0;
};

#endif //SEAL_MAPPER_HPP
