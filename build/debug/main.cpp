#include "lz1.hpp"

int main(int argc, const char **argv)
{
    // std::ios::sync_with_stdio(false); // put here for now...
    // std::cin.tie(NULL);

    //size_t uncompressed_bytes = 0;
    //size_t compressed_bytes = 0;
    //uncompressed_bytes = fs::file_size(file);
 
    auto file = get_file(argc, argv);

    auto triples = lz1_compress_file(file);

    for (const auto& triple : triples) {
        std::println("{}", triple.to_string());
    }
    
}
