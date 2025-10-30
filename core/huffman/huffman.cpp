#include "huffman.hpp"

// **********************************

HuffmanNode::HuffmanNode(Token token, size_t frequency) noexcept :
    token_{ token },
    frequency_{ frequency },
    left_{ nullptr },
    right_{ nullptr }
{}

HuffmanNode::HuffmanNode(size_t frequency) noexcept :
    token_{},
    frequency_{ frequency },
    left_{ nullptr },
    right_{ nullptr }
{}

HuffmanNode::~HuffmanNode()
{
    delete left_;
    delete right_;
}

// **********************************

void HuffmanTree::build(const std::unordered_map<Token, size_t>& freq_table)
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

// **********************************

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

// **********************************

void build_huffman_table(
    const HuffmanNode* node, 
    HuffmanCode& cur_code,
    std::unordered_map<Token, HuffmanCode>& table)
{
    if (node == nullptr) {
        return;
    }

    if (node->left_ == nullptr && node->right_ == nullptr) {
        table[node->token_] = cur_code;
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

// **********************************

std::unordered_map<char, size_t> build_freq_table(fs::path input_file)
{
    std::unordered_map<char, size_t> symbol_counts{}; 

    auto ifs = std::ifstream{input_file};

    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {
            for (auto c : line) {
                symbol_counts[c] += 1;
            }
        }

        ifs.close();
    }

    return symbol_counts;
}