#include <fstream>

#include "parse/parse.hpp"
#include "huffman/HuffmanTree.hpp"
#include "huffman/HuffmanCode.hpp"

void compress(fs::path input_file)
{
    auto freq_table = build_freq_table(input_file);
    auto huffman_tree = HuffmanTree{};
    huffman_tree.build(freq_table);   

    HuffmanCode cur_code;
    std::unordered_map<char, HuffmanCode> huffman_table;
    build_huffman_table(huffman_tree.root, cur_code, huffman_table);

    auto ifs = std::ifstream{input_file};
    auto ofs = std::ofstream{"file.mgw", std::ios::binary};

    std::vector<uint8_t> magic_num{0x01, 0x34}; // compressed mgw files magic number -> 308 -> 0x134

    constexpr size_t N = 8;
    std::array<uint64_t, N> buffer;

    uint64_t bit_buffer = 0;
    int bits_in_buffer = 0;

    // for every write to the uint64_t buffer, we are going to check
    // if some multiple of 8 bits is in the buffer, if so, we flush those bytes to some other buffer / queue / stream

    std::string line;
    while (getline(ifs, line)) {
        for (const auto& symbol : line) {
            auto code = huffman_table[symbol];

            if (bits_in_buffer + code.len_ <= 64) {
                bit_buffer |= (code.bits_ << bits_in_buffer);
                bits_in_buffer += code.len_;
            }
        }
    }   
}

void decompress(fs::path input_file)
{

}