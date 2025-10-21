#include <span>
#include <print>
#include <ranges>
#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "parse.hpp"
#include "huffman.hpp"

int main(int argc, const char **argv)
{
    auto input_file = get_file(argc, argv);
    
    auto symbol_counts = get_symbol_counts(input_file);

    auto heap = build_huffman_heap(symbol_counts);

    while (!heap.empty()) {
        auto& node = heap.top();
        std::println("{}", node->to_string());
        heap.pop();
    }
}
