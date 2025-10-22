#include <print>

#include "parse/parse.hpp"
#include "huffman/HuffmanTree.hpp"
#include "huffman/HuffmanCode.hpp"

int main(int argc, const char **argv)
{
    /*
    auto freq_table = build_freq_table(get_file(argc, argv));
    auto huffman_tree = HuffmanTree{};
    huffman_tree.build(freq_table);   
    */

    std::array<uint64_t, 256> huffman_table{ 0 };

    char symbol = 'e';

    HuffmanCode code;
    code.push_back(1);
    code.push_back(0);
    code.push_back(1);
    code.push_back(1);
    code.push_back(1);
    code.pop_back();
    code.pop_back();

    std::println("{:064b}", code.pack());


    /*
    uint64_t packed = 0;
    std::println("{:064b}", packed);

    std::println("{:064b}", (static_cast<uint64_t>(code.num_bits()) << 56));

    packed = (static_cast<uint64_t>(code.num_bits()) << 56) | code.code;
    std::println("{:064b}", packed);

    */

    
    
    
    
    
    
    

}
