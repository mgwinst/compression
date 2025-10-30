#pragma once

#include <unordered_map>
#include <filesystem>
#include <ranges>
#include <span>

namespace fs = std::filesystem;
namespace ranges = std::ranges;
namespace views = std::views;

struct ProgramInfo
{
    fs::path file_path;
    bool decompress;
    bool encrypt;
    bool image;

    ProgramInfo() : file_path{}, decompress{ false }, encrypt{ false }, image{ false } {}
};

template <ranges::range R>
std::optional<fs::path> get_file_path(R&& args)
{
    auto file_path = fs::path(args.back());

    if (!fs::exists(file_path)) {
        return std::nullopt;
    }

    return file_path;
}

ProgramInfo parse_args(int argc, const char **argv);