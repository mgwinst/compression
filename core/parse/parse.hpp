#pragma once

#include <unordered_map>
#include <filesystem>
#include <ranges>
#include <span>

namespace fs = std::filesystem;
namespace views = std::views;

fs::path get_file(int argc, const char **argv);
std::unordered_map<char, size_t> build_freq_table(fs::path input_file);
