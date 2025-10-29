#pragma once

#include <cstdint>
#include <format>

struct Token
{
    uint16_t distance_;
    uint8_t match_len_;
    uint8_t byte_after_match_;

    Token() : distance_{ 0 }, match_len_{ 0 }, byte_after_match_{ 0 } {}

    Token(uint16_t distance, uint8_t match_len, uint8_t byte_after_match) :
        distance_{ distance }, 
        match_len_{ match_len }, 
        byte_after_match_{ byte_after_match } {}

    Token(const Token& other) : 
        distance_{ other.distance_ }, 
        match_len_{ other.match_len_ }, 
        byte_after_match_{ other.byte_after_match_ } {}

    Token& operator=(const Token& other)
    {
        distance_ = other.distance_;
        match_len_ = other.match_len_;
        byte_after_match_ = other.byte_after_match_;

        return *this;
    }

    auto to_string() const
    {
        return std::format("Token<{},{},{}>", distance_, match_len_, static_cast<char>(byte_after_match_));
    }
};