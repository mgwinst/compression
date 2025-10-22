#pragma once

#include <unordered_map>
#include <queue>
#include <vector>

#include "HuffmanNode.hpp"

struct HuffmanTree
{
    HuffmanNode* root{ nullptr };

    void build(const std::unordered_map<char, size_t>& freq_table);
};

template<typename Compare> 
using HuffmanHeap = std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, Compare>;