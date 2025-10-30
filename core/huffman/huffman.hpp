#pragma once

#include <unordered_map>
#include <cstddef>
#include <queue>
#include <vector>

#include "core/token.hpp"

// instead of char, should be token

struct HuffmanNode
{
    Token token_;
    size_t frequency_;
    HuffmanNode* left_;
    HuffmanNode* right_;

    HuffmanNode(Token token, size_t frequency) noexcept;
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

    void build(const std::unordered_map<Token, size_t>& freq_table);
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
    std::unordered_map<Token, HuffmanCode>& codes
);

/*
    auto freq_table = build_freq_table(input_file);
    auto huffman_tree = HuffmanTree{};
    huffman_tree.build(freq_table);   
    HuffmanCode huffman_code{};
    std::unordered_map<char, HuffmanCode> huffman_table;
    build_huffman_table(huffman_tree.root, huffman_code, huffman_table);
*/