#include "days.hpp"

#include <algorithm>
#include <vector>

#include <iostream>

static unsigned int follow_binary_path(std::string path, char upper_letter, unsigned int starting_value) {
    unsigned int current_value = 0;
    unsigned int current_step = starting_value;

    for(auto letter: path) {
        current_step /= 2;
        if(letter == upper_letter) {
            current_value += current_step;
        }
    }
    return current_value;
}

unsigned int binary_set_search(const std::vector<std::string> input_data) {
    std::vector<int> found_seats;

    for(auto boarding_pass: input_data) {
        auto row_description = boarding_pass.substr(0,7);
        auto column_description = boarding_pass.substr(7,3);

        const int row = follow_binary_path(row_description, 'B', 128);
        const int column = follow_binary_path(column_description, 'R', 8);

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
