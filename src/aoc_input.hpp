#pragma once

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc {

template <typename T>
std::vector<T> read_input_tokenwise(const std::string file_location) {
    std::ifstream input_data(file_location);
    std::vector<T> input;
    T tmp;
    while( input_data >> tmp) {
        input.push_back(tmp);
    }
    return input;
}

std::vector<std::string> read_input_linewise(const std::string file_location);
}
