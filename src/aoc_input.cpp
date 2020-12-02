#include "aoc_input.hpp"

std::vector<std::string> aoc::read_input_linewise(std::string file_location) {
    std::ifstream input_data(file_location);
    std::string line;
    std::vector<std::string> input;
    while(std::getline(input_data, line)) {
        input.push_back(line);
    }
    return input;
}
