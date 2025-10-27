#include <fstream>

#include "parse/parse.hpp"

void decompress(fs::path input_file)
{
    auto ifs = std::ifstream{ input_file };

    std::string line;
    while (getline(ifs, line)) {

    }



    
}