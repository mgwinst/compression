#include <fstream>

#include "parse/parse.hpp"
#include "huffman/huffman.hpp"

void compress(fs::path input_file)
{
    auto freq_table = build_freq_table(input_file);
    auto huffman_tree = HuffmanTree{};
    huffman_tree.build(freq_table);   
    HuffmanCode huffman_code{};
    std::unordered_map<char, HuffmanCode> huffman_table;
    build_huffman_table(huffman_tree.root, huffman_code, huffman_table);

    auto ifs = std::ifstream{ input_file };
    auto ofs = std::ofstream{"file.mgw", std::ios::binary};

    // encode_huffman_table(ofs, huffman_table);

    std::vector<uint64_t> byte_buffer;
    size_t total_bytes_written = 0;
    __uint128_t bit_buffer = 0;
    uint8_t bits_in_buffer = 0;

    std::string line;
    while (getline(ifs, line)) {
        for (const auto& symbol : line) {
            auto code = huffman_table[symbol];
            bit_buffer |= (code.bits_ << bits_in_buffer);
            bits_in_buffer += code.len_;

            if (bits_in_buffer >= 64) {
                uint64_t codes_to_copy = bit_buffer & UINT64_MAX;
                bit_buffer >>= 64;
                bits_in_buffer -= 64;
                byte_buffer.push_back(codes_to_copy);
            }
        }
        
        ofs.write(reinterpret_cast<const char *>(byte_buffer.data()), byte_buffer.size() * sizeof(uint64_t));
        total_bytes_written += byte_buffer.size();
        byte_buffer.clear();
    }

    if (bits_in_buffer > 0) {
        uint8_t padded_bits = 64 - bits_in_buffer;
        bit_buffer <<= padded_bits;
        ofs.write(reinterpret_cast<const char *>(&bit_buffer), sizeof(uint64_t));
    }
}

