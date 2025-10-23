#include "HuffmanCode.hpp"

void HuffmanCode::push_back(bool bit) noexcept
{
    bits_ = (bits_ << 1) | static_cast<uint64_t>(bit);
    len_ += 1;
}

void HuffmanCode::pop_back() noexcept
{
    bits_ = (bits_ >> 1);
    len_ -= 1;
}

void build_huffman_table(
    const HuffmanNode* node, 
    HuffmanCode& cur_code,
    std::unordered_map<char, HuffmanCode>& table)
{
    if (node == nullptr) {
        return;
    }

    if (node->left_ == nullptr && node->right_ == nullptr) {
        table[node->symbol_] = cur_code;
        return;
    }

    if (node->left_) {
        cur_code.push_back(0);
        build_huffman_table(node->left_, cur_code, table);
        cur_code.pop_back();
    }

    if (node->right_) {
        cur_code.push_back(1);
        build_huffman_table(node->right_, cur_code, table);
        cur_code.pop_back();
    }

    return;
}