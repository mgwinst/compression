#pragma once

#include <cstddef>
#include <memory>
#include <queue>
#include <format>

struct HuffmanNode;

using HuffmanNodePtr = std::unique_ptr<HuffmanNode>;

struct HuffmanNode
{
    char symbol_;
    size_t frequency_;
    HuffmanNodePtr left_;
    HuffmanNodePtr right_;

    HuffmanNode(char symbol, size_t frequency) :
        symbol_{ symbol },
        frequency_{ frequency },
        left_{ nullptr },
        right_{ nullptr }
    {}

    auto to_string() { return std::format("Node('{}' : {})", symbol_, frequency_); }
};

struct NodeCompare
{
    bool operator()(const HuffmanNodePtr& a, const HuffmanNodePtr& b)
    {
        return a->frequency_ > b->frequency_;
    }
};

using HuffmanMinHeap = std::priority_queue<HuffmanNodePtr, std::vector<HuffmanNodePtr>, NodeCompare>;

HuffmanMinHeap build_huffman_heap(std::unordered_map<char, size_t> freq_table)
{
    HuffmanMinHeap min_heap;

    for (const auto& elem : freq_table)
        min_heap.emplace(std::make_unique<HuffmanNode>(elem.first, elem.second));
    
    return min_heap;
}
