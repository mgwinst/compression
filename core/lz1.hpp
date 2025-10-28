#pragma once

#include <cstring>
#include <fstream>
#include <print>
#include <iostream>
#include <array>
#include <list>
#include <string>
#include <cstdlib>

#include "parse/parse.hpp"
#include "huffman/huffman.hpp"
#include "core/hash.hpp"
#include "core/token.hpp"

#define MIN_MATCH 3
#define MAX_MATCH 258
#define WINDOW_SIZE (1 << 16)
#define HASH_TABLE_SIZE (1 << 16)
#define CHUNK_SIZE (1 << 16)

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

inline void lz1_compress(const fs::path& file)
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

    std::array<std::list<uint64_t>, HASH_TABLE_SIZE> table{};

    std::vector<uint8_t> input_buffer;
    input_buffer.reserve(CHUNK_SIZE);
    std::vector<Token> output_buffer;
    output_buffer.reserve(CHUNK_SIZE);

    input_file.read((char*)(input_buffer.data()), fs::file_size(file));

    for (int i = 0; i < input_file.gcount(); i++) {
        std::print("{}", (char)input_buffer[i]);
    }

    std::println();
    std::println();

    size_t i = 0;

    // hashing 3 bytes will cause error on end of buffer...
    while (i < input_file.gcount())  {
        auto hash = djb2_hash(&input_buffer[i]);
        auto prefix_chain = table[hash];

        if (prefix_chain.empty()) {
            output_buffer.push_back(Token{0, 0, input_buffer[i]});
            prefix_chain.push_back(i);
            i++;
        } else {
            ByteMatch biggest_match{0, 0};
            for (const auto& j : views::reverse(prefix_chain)) {
                if (i - j <= WINDOW_SIZE) {
                    if (prefix_match(&input_buffer[j], &input_buffer[i])) {
                        auto mismatch_byte = std::mismatch(&input_buffer[j], &input_buffer[j + MAX_MATCH - 1], &input_buffer[i]);
                        if (mismatch_byte.first != &input_buffer[j + MAX_MATCH]) {
                            uint32_t num_matching_bytes = (std::distance(&input_buffer[j], mismatch_byte.first));
                            if (num_matching_bytes > biggest_match.match_len) {
                                biggest_match = ByteMatch{j, num_matching_bytes};
                            }
                        }
                    }
                }
            }

            output_buffer.push_back(Token{static_cast<uint16_t>(i - biggest_match.index), static_cast<uint8_t>(biggest_match.match_len), input_buffer[i + biggest_match.match_len]});
            prefix_chain.push_back(i);
            i += biggest_match.match_len;
        }
    }

    for (const auto& token : output_buffer) {
        std::println("{}", token.to_string());
    }
}