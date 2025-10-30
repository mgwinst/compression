#include <array>
#include <print>

#include "parse/parse.hpp"

int main(int argc, const char **argv)
{
    // std::ios::sync_with_stdio(false); // put here for now...
    // std::cin.tie(NULL);

    //size_t uncompressed_bytes = 0;
    //size_t compressed_bytes = 0;
    //uncompressed_bytes = fs::file_size(file);

    // auto triples = lz1_compress_file(file);
 
    auto program_info = parse_args(argc, argv);

    std::println();
    std::println("file path:  {}", program_info.file_path.string());
    std::println("decompress? {}", program_info.decompress ? "true" : "false");
    std::println("encrypt?    {}", program_info.encrypt ? "true" : "false");
    std::println("image?      {}", program_info.image ? "true" : "false");

}
