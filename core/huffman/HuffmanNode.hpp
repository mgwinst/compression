#pragma once

#include <cstddef>
#include <format>

struct HuffmanNode
{
    char symbol_;
    size_t frequency_;
    HuffmanNode* left_;
    HuffmanNode* right_;

    HuffmanNode(char symbol, size_t frequency) noexcept;
    HuffmanNode(size_t frequency) noexcept;
    ~HuffmanNode();

    auto to_string() const noexcept
    {
        return std::format("Node('{}' : {})", symbol_, frequency_);
    }

};

struct HuffmanNodeCompare
{
    bool operator()(const HuffmanNode* a, const HuffmanNode* b)
    {
        return a->frequency_ > b->frequency_;
    }
};