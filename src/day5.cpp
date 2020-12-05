#include "days.hpp"

#include <algorithm>
#include <vector>

#include <iostream>

// Use instead of math's std::pow, because I only need integers and powers of two
static unsigned int pow_2(const unsigned int value) {
    return 1 << value;
}

static unsigned int follow_binary_path(const std::string path, const char upper_letter, const unsigned int path_len) {
    unsigned int current_value = 0;
    unsigned int current_step = path_len;

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
    constexpr unsigned int row_path_len = 7;
    constexpr unsigned int column_path_len  = 3;

    for(auto boarding_pass: input_data) {
        auto row_description = boarding_pass.substr(0, row_path_len);
        auto column_description = boarding_pass.substr(7, column_path_len);

        const unsigned int row = follow_binary_path(row_description, 'B', pow_2(row_path_len));
        const unsigned int column = follow_binary_path(column_description, 'R', pow_2(column_path_len));

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