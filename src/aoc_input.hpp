#pragma once


#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>

namespace aoc {

template <typename T>
std::vector<T> read_input(std::string file_location) {
    std::ifstream input_data(file_location);
    std::vector<T> input;
    T tmp;
    while( input_data >> tmp) {
        input.push_back(tmp);
    }
    if(input_data.fail()) {
        throw std::invalid_argument("Input does not match data type");
    }
    return input;
}

}
