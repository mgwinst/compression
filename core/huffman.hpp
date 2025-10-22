#pragma once

#include <cstddef>
#include <memory>
#include <queue>
#include <format>
#include <vector>

struct HuffmanNode
{
    char symbol_;
    size_t frequency_;
    HuffmanNode* left_;
    HuffmanNode* right_;

    HuffmanNode(char symbol, size_t frequency) :
        symbol_{ symbol },
        frequency_{ frequency },
        left_{ nullptr },
        right_{ nullptr }
    {}

    HuffmanNode(size_t frequency) :
        symbol_{},
        frequency_{ frequency },
        left_{ nullptr },
        right_{ nullptr }
    {}

    ~HuffmanNode()
    {
        delete left_;
        delete right_;
    }

    auto to_string() const noexcept { return std::format("Node('{}' : {})", symbol_, frequency_); }
};

struct NodeCompare
{
    bool operator()(const HuffmanNode* a, const HuffmanNode* b)
    {
        return a->frequency_ > b->frequency_;
    }
};

using HuffmanHeap = std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, NodeCompare>;

HuffmanNode* build_huffman_tree(std::unordered_map<char, size_t> freq_table)
{
    HuffmanHeap min_heap;

    for (const auto& elem : freq_table)
        min_heap.push(new HuffmanNode(elem.first, elem.second));
    
    while (min_heap.size() > 1) {
        auto a = min_heap.top();
        min_heap.pop();
        auto b = min_heap.top();
        min_heap.pop();
        
        auto parent = new HuffmanNode(a->frequency_ + b->frequency_);
        parent->left_ = a;
        parent->right_ = b;

        min_heap.push(parent);
    }
    
    return min_heap.top();
}

std::unordered_map<char, std::vector<bool>>&
build_huffman_codes(
    const HuffmanNode* node, 
    std::vector<bool>& cur_code,
    std::unordered_map<char, std::vector<bool>>& codes)
{
    if (node->left_ == nullptr && node->right_ == nullptr) {
        codes[node->symbol_] = cur_code;
        return codes;
    }

    if (node->left_) {
        cur_code.push_back(0);
        build_huffman_codes(node->left_, cur_code, codes);
        cur_code.pop_back();
    }

    if (node->right_) {
        cur_code.push_back(1);
        build_huffman_codes(node->right_, cur_code, codes);
        cur_code.pop_back();
    }

    return codes;
}