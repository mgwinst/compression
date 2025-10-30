#pragma once

#include <cstdint>
#include <format>

struct Triple
{
    uint16_t distance_;
    uint8_t match_len_;
    uint8_t literal_after_match_;

    Triple() noexcept : 
        distance_{ 0 },
        match_len_{ 0 },
        literal_after_match_{ 0 } {}

    Triple(uint16_t distance, uint8_t match_len, uint8_t literal_after_match) noexcept :
        distance_{ distance }, 
        match_len_{ match_len }, 
        literal_after_match_{ literal_after_match } {}

    Triple(const Triple& other) noexcept : 
        distance_{ other.distance_ }, 
        match_len_{ other.match_len_ }, 
        literal_after_match_{ other.literal_after_match_ } {}

    Triple& operator=(const Triple& other) noexcept
    {
        distance_ = other.distance_;
        match_len_ = other.match_len_;
        literal_after_match_ = other.literal_after_match_;

        return *this;
    }

    Triple(Triple&&) = default;
    Triple& operator=(Triple&&) = default;
    ~Triple() = default;

    auto to_string() const noexcept
    {
        return std::format("Triple<{},{},{}>", distance_, match_len_, static_cast<char>(literal_after_match_));
    }
};