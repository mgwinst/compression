#include <print>
#include <iostream>
#include <fstream>
#include <list>
#include <array>
#include <ranges>
#include <algorithm>
#include <span>

#include "parse/parse.hpp"
#include "huffman/huffman.hpp"
#include "hash.hpp"

#define MIN_MATCH 3
#define MAX_MATCH 258
#define WINDOW_SIZE (1 << 16)
#define HASH_TABLE_SIZE (1 << 16)

namespace rng = std::ranges;
namespace views = std::views;

inline auto prefix_match(const uint8_t *p1, const uint8_t *p2)
{
    return std::memcmp(p1, p2, 3) == 0;
}

int main(int argc, const char **argv)
{
    // std::ios::sync_with_stdio(false); // put here for now...
    // std::cin.tie(NULL);

    auto input_file = get_file(argc, argv);
    auto uncompressed_bytes = std::filesystem::file_size(input_file);

    auto file = std::ifstream{ input_file };
    if (!file.is_open()) {
        std::println(std::cerr, "Failed to open file.");
        return 1;
    }

    std::array<std::list<uint64_t>, HASH_TABLE_SIZE> table{};

    constexpr size_t CHUNK_SIZE = 1 << 16;
    std::vector<uint8_t> input_buffer(CHUNK_SIZE);
    std::vector<__uint128_t> output_buffer(CHUNK_SIZE);
    __uint128_t bit_buffer = 0;

    size_t num_chunks = 1;
    size_t i = 0;
    while (file.read(reinterpret_cast<char *>(input_buffer.data()), CHUNK_SIZE)) {
        while (i < CHUNK_SIZE * num_chunks) {
            auto hash = djb2_hash(&input_buffer[i]); 
            auto prefix_chain = table[hash];

            if (prefix_chain.empty()) {
                // emit literal
                // prefix_chain.push_back(i);
                // i++;
            } else {
                std::pair<uint64_t, uint32_t> biggest_match; // pair<index, match_len>
                for (const auto& j : views::reverse(prefix_chain)) {
                    if (i - j <= WINDOW_SIZE) {
                        if (prefix_match(&input_buffer[j], &input_buffer[i])) [[likely]] {
                            auto mismatch_byte = std::mismatch(&input_buffer[j], &input_buffer[j + MAX_MATCH - 1], &input_buffer[i]);
                            if (mismatch_byte.first != &input_buffer[j + MAX_MATCH]) {
                                auto num_matching_bytes = static_cast<uint32_t>(std::distance(&input_buffer[j], mismatch_byte.first));
                                if (num_matching_bytes > biggest_match.second) {
                                    biggest_match = std::pair<uint64_t, uint32_t>{j, num_matching_bytes};
                                }
                            }
                        }
                    }
                }
                // emit token
                // prefix_chain.push_back(i);
                // i += biggest_match;
            }
        }
        num_chunks++;   
    }

    if (file.gcount() > 0) {
        // process remaining bytes from failed final read
    }
}
