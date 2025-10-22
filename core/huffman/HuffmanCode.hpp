#pragma once

#include <vector>
#include <unordered_map>

#include "HuffmanCode.hpp"
#include "HuffmanNode.hpp"

class HuffmanCode
{
public:
    void push_back(bool bit) noexcept;
    void pop_back() noexcept;
    auto to_string() const noexcept;

private:
    std::vector<bool> code;
    size_t len;
};

std::unordered_map<char, int64_t>& build_huffman_codes(
    const HuffmanNode* node, 
    HuffmanCode& cur_code,
    std::unordered_map<char, int64_t>& codes);