#ifndef SEAL_BUS_HPP
    #define SEAL_BUS_HPP
    #include <cstdint>
    #include <array>
    #include "Core.hpp"

    #define IS_16_BIT(a) a >= 0x0000 && a <= 0xFFFF

class Bus {
public:
    Bus();
    ~Bus();

    Core cpu;

    std::array<uint8_t, 64 * 1024> ram;

    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool readOnly = false);
};

#endif //SEAL_BUS_HPP
