#pragma once

#include <vector>
#include <unordered_map>
#include <array>
#include <utility>

#include "HuffmanCode.hpp"
#include "HuffmanNode.hpp"

struct HuffmanCode
{
    uint64_t bits_{ 0 };
    uint8_t len_{ 0 };

    void push_back(bool bit) noexcept;
    void pop_back() noexcept;
};

void build_huffman_table(
    const HuffmanNode* node, 
    HuffmanCode& cur_code,
    std::unordered_map<char, HuffmanCode>& codes);