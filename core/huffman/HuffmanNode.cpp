#include "HuffmanNode.hpp"

HuffmanNode::HuffmanNode(char symbol, size_t frequency) noexcept :
    symbol_{ symbol },
    frequency_{ frequency },
    left_{ nullptr },
    right_{ nullptr }
{}

HuffmanNode::HuffmanNode(size_t frequency) noexcept :
    symbol_{},
    frequency_{ frequency },
    left_{ nullptr },
    right_{ nullptr }
{}

HuffmanNode::~HuffmanNode()
{
    delete left_;
    delete right_;
}