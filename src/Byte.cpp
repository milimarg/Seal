/*
** EPITECH PROJECT, 2024
** Seal
** File description:
** Byte.cpp
*/

#include "../includes/Byte.hpp"

uint8_t Byte::flipByte(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0xCC) << 2;
    b = (b & 0xAA) >> 1 | (b & 0xAA) << 1;
    return b;
}

std::string Byte::hex(uint32_t n, uint8_t d)
{
    std::string s(d, '0');

    for (int i = d - 1; i >= 0; --i) {
        s[i] = "0123456789ABCDEF"[n & 0xF];
        n >>= 4;
    }
    return s;
}
