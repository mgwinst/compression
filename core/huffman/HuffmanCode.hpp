#pragma once

#include <vector>
#include <unordered_map>
#include <array>

#include "HuffmanCode.hpp"
#include "HuffmanNode.hpp"

struct HuffmanCode
{
    uint64_t code{ 0 };
    uint8_t len{ 0 };

    void push_back(bool bit) noexcept;
    void pop_back() noexcept;
    uint64_t pack() noexcept;

    // void unpack() noexcept;

    auto num_bits() const noexcept { return len; }
};