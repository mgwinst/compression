#include <span>
#include <print>
#include <ranges>
#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "parse/parse.hpp"
#include "huffman/HuffmanTree.hpp"

int main(int argc, const char **argv)
{
    auto freq_table = build_freq_table(get_file(argc, argv));

    auto huffman_tree = HuffmanTree{};

    huffman_tree.build(freq_table);   

    
    


    /*

    std::unordered_map<char, int64_t> code_table;
    int64_t cur_code = 0x00000000;

    HuffmanCode code;

    code.append_new_bit(0);
    code.append_new_bit(0);
    code.append_new_bit(1);
    code.append_new_bit(1);
    code.append_new_bit(0);

    std::println("{}", code.to_string());

    */
    
    
    
    
    
    
    
    

}
