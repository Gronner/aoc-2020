#include "days.hpp"

#include <iostream>
#include <vector>

#include "aoc_input.hpp"

unsigned int expense_report(std::vector<unsigned int> input_data) {
    for(auto val1: input_data) {
        for(auto val2: input_data) {
            for(auto val3: input_data) {
                if(2020 == (val1 + val2 + val3)) {
                    return val1 * val2 * val3;
                }
            }
        }
    }
    return 0;
}
