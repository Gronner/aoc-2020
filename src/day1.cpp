#include <iostream>

#include "aoc_input.hpp"

void day1() {
    auto input_data = aoc::read_input<unsigned int>("../data/day1.txt");
    for(auto val1: input_data) {
        for(auto val2: input_data) {
            for(auto val3: input_data) {
                if(2020 == (val1 + val2 + val3)) {
                    std::cout << val1 << " " << val2 << " " << val3 << std::endl;
                    std::cout << val1 * val2 * val3 << std::endl;
                    return;
                }
            }
        }
    }
}
