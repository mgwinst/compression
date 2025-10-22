#include "HuffmanTree.hpp"

#include <print>

void HuffmanTree::build(const std::unordered_map<char, size_t>& freq_table)
{
    HuffmanHeap<HuffmanNodeCompare> min_heap;

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
    
    root = min_heap.top();
}