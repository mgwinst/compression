#pragma once

#include <cstring>
#include <fstream>
#include <print>
#include <iostream>
#include <array>
#include <list>
#include <string>
#include <cstdlib>
#include <vector>

#include "parse/parse.hpp"
// #include "huffman/huffman.hpp"
#include "core/hash.hpp"
#include "core/triple.hpp"

#define MIN_MATCH 3
#define MAX_MATCH 258
#define WINDOW_SIZE (1 << 16)
#define HASH_TABLE_SIZE (1 << 16)

namespace views = std::views;

struct ByteMatch
{
    uint64_t index;
    uint32_t match_len;
};

inline auto prefix_match(const uint8_t *p1, const uint8_t *p2)
{
    return std::memcmp(p1, p2, 3) == 0;
}

inline std::vector<Triple> lz1_compress_file(const fs::path& file)
{
    auto input_file = std::ifstream{file, std::ios::binary};
    if (!input_file.is_open()) {
        std::println(std::cerr, "Failed to open input file.");
        exit(EXIT_FAILURE);
    }

    auto output_file = std::ofstream{(file.stem().string() + ".mgw"), std::ios::binary};
    if (!output_file.is_open()) {
        std::println(std::cerr, "Failed to create/open output file.");
        exit(EXIT_FAILURE);
    }

    auto table = std::array<std::list<uint64_t>, HASH_TABLE_SIZE>{};
    auto file_buffer = std::unique_ptr<uint8_t[]>(new uint8_t[fs::file_size(file) + 2]); // + 2 bytes for final hash
    auto token_buffer = std::vector<Triple>{};

    input_file.read((char*)(file_buffer.get()), fs::file_size(file));

    size_t i = 0;
    while (i < input_file.gcount())  {
        auto hash = djb2_hash(&file_buffer[i]);
        auto& prefix_chain = table[hash % HASH_TABLE_SIZE];

        if (prefix_chain.empty()) {
            token_buffer.push_back(Triple{0, 0, file_buffer[i]});
            prefix_chain.push_back(i);
            i++;
        } else {
            ByteMatch biggest_match{0, 0};

            for (const auto& j : views::reverse(prefix_chain)) {
                if (i - j <= WINDOW_SIZE) {
                    if (prefix_match(&file_buffer[j], &file_buffer[i])) {
                        auto mismatch_byte = std::mismatch(&file_buffer[j], &file_buffer[j + MAX_MATCH - 1], &file_buffer[i]);
                        if (mismatch_byte.first != &file_buffer[j + MAX_MATCH]) {
                            uint32_t num_matching_bytes = (std::distance(&file_buffer[j], mismatch_byte.first));
                            if (num_matching_bytes > biggest_match.match_len) {
                                biggest_match = ByteMatch{j, num_matching_bytes};
                            }
                        }
                    }
                }
            }

            if (biggest_match.match_len < 3) {
                token_buffer.push_back(Triple{0, 0, file_buffer[i]});
                prefix_chain.push_back(i);
                i++;
            } else {
                token_buffer.push_back(Triple{static_cast<uint16_t>(i - biggest_match.index), static_cast<uint8_t>(biggest_match.match_len), file_buffer[i + biggest_match.match_len]});
                prefix_chain.push_back(i);
                i += (biggest_match.match_len + 1); // include literal after match
            }
        }
    }

    return token_buffer; 
}
