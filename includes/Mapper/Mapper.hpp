#ifndef SEAL_MAPPER_BASE_HPP
    #define SEAL_MAPPER_BASE_HPP
    #include <cstdint>

class Mapper {
public:
    Mapper(uint8_t prgBanks, uint8_t chrBanks);
    ~Mapper();

    virtual bool cpuMapRead(uint16_t address, uint32_t &mapped_addr) = 0;
    virtual bool cpuMapWrite(uint16_t address, uint32_t &mapped_addr, uint8_t data = 0) = 0;
    virtual bool ppuMapRead(uint16_t address, uint32_t &mapped_addr) = 0;
    virtual bool ppuMapWrite(uint16_t address, uint32_t &mapped_addr) = 0;

    virtual void reset() = 0;

protected:
    uint8_t _PrgBanks = 0;
    uint8_t _ChrBanks = 0;
};

#endif //SEAL_MAPPER_BASE_HPP
