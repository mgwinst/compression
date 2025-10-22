#include <fstream>

#include "parse.hpp"

fs::path get_file(int argc, const char **argv)
{
    std::span<const char *> arguments{argv, static_cast<size_t>(argc)};
    
    auto args = arguments | views::drop(1);
    
    fs::path input_file{ args.back() };
    if (!fs::exists(input_file)) {
        throw std::runtime_error("file doesn't not exist");
    }

    return input_file;
}

std::unordered_map<char, size_t> build_freq_table(fs::path input_file)
{
    std::unordered_map<char, size_t> symbol_counts{}; 

    auto ifs = std::ifstream{input_file};

    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {
            for (auto c : line) {
                symbol_counts[c] += 1;
            }
        }

        ifs.close();
    }

    return symbol_counts;
}
