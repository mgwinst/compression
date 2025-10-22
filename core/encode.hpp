#include <fstream>

#include "parse/parse.hpp"
#include "huffman.hpp"

void encode(fs::path input_file)
{
    auto symbol_counts = get_symbol_counts(input_file);

    std::unordered_map<char, std::vector<bool>> codes{};
    std::vector<bool> cur_code{};

    auto root = build_huffman_tree(symbol_counts);
    auto code_table = build_huffman_codes(root, cur_code, codes);

    auto output_file = std::ofstream{"file.mgw", std::ios::binary};

    std::vector<std::byte> magic_num{std::byte{0x01}, std::byte{0x34}};

    std::vector<bool>
 


    



    
}

void decode(fs::path input_file)
{

}