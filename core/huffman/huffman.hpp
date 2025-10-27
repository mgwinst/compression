#pragma once

#include <unordered_map>
#include <cstddef>
#include <queue>
#include <vector>

struct HuffmanNode
{
    char symbol_;
    size_t frequency_;
    HuffmanNode* left_;
    HuffmanNode* right_;

    HuffmanNode(char symbol, size_t frequency) noexcept;
    HuffmanNode(size_t frequency) noexcept;
    ~HuffmanNode();
};

struct HuffmanNodeCompare
{
    bool operator()(const HuffmanNode* a, const HuffmanNode* b)
    {
        return a->frequency_ > b->frequency_;
    }
};

struct HuffmanTree
{
    HuffmanNode* root{ nullptr };

    void build(const std::unordered_map<char, size_t>& freq_table);
};

template<typename Compare> 
using HuffmanHeap = std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, Compare>;

struct HuffmanCode
{
    __uint128_t bits_{ 0 };
    uint8_t len_{ 0 };

    void push_back(bool bit) noexcept;
    void pop_back() noexcept;
};

void build_huffman_table(
    const HuffmanNode* node, 
    HuffmanCode& cur_code,
    std::unordered_map<char, HuffmanCode>& codes
);