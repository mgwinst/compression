#include <iostream>
#include <print>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

#include "parse.hpp"

void print_pac_usage()
{
    std::println("usage: pac [-options] [file/directory/image...]");
}

void print_pac_help()
{
    std::println("pac: a lightweight compression tool");
    std::println("usage: pac [-options] [file/directory/image...]");
    std::println("options:");
    std::println("  [-d] -> decompress file");
    std::println("  [-e] -> encrypt file");
    std::println("  [-i] -> image file");
    std::println("  [-h] -> help");
}

ProgramInfo parse_args(int argc, const char **argv)
{
    ProgramInfo prog_info;

    std::unordered_set<std::string> flags {
        "-d", "-decompress",
        "-e", "-encrypt",
        "-i", "-image",
        "-h", "-help",
    };

    std::span<const char *> arguments{argv, static_cast<size_t>(argc)};
    auto args = arguments | views::drop(1);

    if (args.size() == 0) {
        print_pac_help();
        exit(1);
    } 
    
    auto file_path = get_file_path(args);
    if (!file_path) {
        std::println(std::cerr, "pac: specified path does not exist");
        print_pac_usage();
        exit(1);
    } else {
        prog_info.file_path = *file_path;
    }
    
    if (args.size() > 1) {
        std::unordered_set<std::string> set_flags;
        for (const auto& elem : views::take(args, args.size() - 1)) {
            if (!flags.contains(elem)) {
                std::println(std::cerr, "pac: invalid option [{}]", elem);
                print_pac_usage();
                exit(1);
            }

            if (set_flags.contains(elem)) {
                print_pac_usage();
                exit(1);
            }

            set_flags.insert(elem);
        }

        prog_info.decompress = set_flags.contains("-d") ? 1 : 0;
        prog_info.encrypt = set_flags.contains("-e") || set_flags.contains("-encrypt") ? 1 : 0;
        prog_info.image = set_flags.contains("-i") || set_flags.contains("-image") ? 1 : 0;
    }

    return prog_info;
}