#ifndef SEAL_MAPPER_000_HPP
    #define SEAL_MAPPER_000_HPP
    #include "Mapper.hpp"

class Mapper_000 : public Mapper {
public:
    Mapper_000(uint8_t prgBanks, uint8_t chrBanks);
    ~Mapper_000();

    bool cpuMapRead(uint16_t address, uint32_t &mapped_addr) override;
    bool cpuMapWrite(uint16_t address, uint32_t &mapped_addr, uint8_t data = 0) override;
    bool ppuMapRead(uint16_t address, uint32_t &mapped_addr) override;
    bool ppuMapWrite(uint16_t address, uint32_t &mapped_addr) override;

    void reset() override;
};

#endif //SEAL_MAPPER_000_HPP
