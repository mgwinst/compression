#pragma once

#include <cstdint>

struct Token
{
    uint32_t bits_ = 0; // [distance/len] [2 bytes, 1 byte] (lsb)

    Token(uint16_t distance, uint8_t len) noexcept
    {
        bits_ = (static_cast<uint32_t>(distance) << 24) | static_cast<uint32_t>(len);
    }
};