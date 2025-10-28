#pragma once

#include <cstdint>
#include <format>

struct Token
{
    const uint16_t distance_;
    const uint8_t match_len_;
    const uint8_t byte_after_match_;

    Token(uint16_t distance, uint8_t match_len, uint8_t byte_after_match) :
        distance_{ distance }, 
        match_len_{ match_len }, 
        byte_after_match_{ byte_after_match } {}

    auto to_string() const
    {
        return std::format("Token<{},{},{}>", distance_, match_len_, byte_after_match_);
    }
};