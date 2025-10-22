#include "HuffmanCode.hpp"

void HuffmanCode::push_back(bool bit) noexcept
{
    code = (code << 1) | static_cast<uint64_t>(bit);
    len += 1;
}

void HuffmanCode::pop_back() noexcept
{
    code = (code >> 1);
    len -= 1;
}

uint64_t HuffmanCode::pack() noexcept
{
    return (static_cast<uint64_t>(len) << 56) | code;
}


/*
std::array<int32_t, 256>& build_huffman_table(
    const HuffmanNode* node, 
    HuffmanCode& cur_code,
    std::unordered_map<char, int64_t>& codes)
{
    if (node == nullptr) {
        return codes;
    }

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

*/