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
    auto root = build_huffman_tree(symbol_counts);
    
    std::unordered_map<char, std::vector<bool>> codes{};
    std::vector<bool> cur_code{};

    for (auto&& elem : build_huffman_codes(root, cur_code, codes)) {
        std::print("{} : ", elem.first);
        for (const auto& b : elem.second) {
            std::print("{}", b ? 1 : 0);
        }
        std::println();
    }
    
    
    

}
