#include "days.hpp"

#include <algorithm>
#include <numeric>
#include <vector>

#include <iostream>

unsigned int binary_set_search(const std::vector<std::string> input_data) {
    std::vector<int> found_seats;

    for(auto boarding_pass: input_data) {
        auto row_description = boarding_pass.substr(0,7);
        auto column_description = boarding_pass.substr(7,3);

        unsigned int current_row = 0;
        size_t current_step = 128;

        for(auto letter: row_description) {
            current_step /= 2;
            if(letter == 'B') {
                current_row += current_step;
            } 
        }
        const int row = current_row;

        std::vector<int> columns(8);
        std::iota(std::begin(columns), std::end(columns), 0);
        unsigned int current_column = 0;
        current_step = 8;

        for(auto letter: column_description) {
            current_step /= 2;
            if(letter == 'R') {
                current_column += current_step;
            }
        }
        const int column = current_column;
        found_seats.push_back(column + 8 * row);
    }

    std::sort(found_seats.begin(), found_seats.end());
    for(size_t i = 1; i < found_seats.size(); i++) {
        if(found_seats[i-1] + 2 == found_seats[i]) {
            return found_seats[i] - 1;
        }
    }
    return 0;
}
