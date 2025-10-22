#include "HuffmanCode.hpp"

void HuffmanCode::push_back(bool bit) noexcept
{
    code.push_back(bit);
    len += 1;
}

void HuffmanCode::pop_back() noexcept
{
    code.pop_back();
    len -= 1;
}

auto HuffmanCode::to_string() const noexcept
{
    std::string s;
    for (const auto& bit : code) {
        s.append(bit ? "1" : "0");
    }
    return s;
}

std::unordered_map<char, int64_t>& build_huffman_codes(
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