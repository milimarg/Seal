/*
** EPITECH PROJECT, 2024
** Seal
** File description:
** Byte.hpp
*/

#ifndef SEAL_BYTE_HPP
    #define SEAL_BYTE_HPP
    #include <cstdint>
#include <iostream>

class Byte {
public:
    static uint8_t flipByte(uint8_t b);
    static std::string hex(uint32_t n, uint8_t d);
private:
    Byte();
    ~Byte();
};

#endif //SEAL_BYTE_HPP
