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

        std::vector<int> rows(128);
        std::iota(std::begin(rows), std::end(rows), 0);
        size_t current_row = 128;

        for(auto letter: row_description) {
            current_row /= 2;
            if(letter == 'F') {
                rows = std::vector<int>(rows.begin(), rows.end() - current_row);
            } else {
                rows = std::vector<int>(rows.begin() + current_row, rows.end());
            }
        }
        const int row = rows[0];

        std::vector<int> columns(8);
        std::iota(std::begin(columns), std::end(columns), 0);
        size_t current_column = 8;

        for(auto letter: column_description) {
            current_column /= 2;
            if(letter == 'L') {
                columns = std::vector<int>(columns.begin(), columns.end() - current_column);
            } else {
                columns = std::vector<int>(columns.begin() + current_column, columns.end());
            }
        }
        const int column = columns[0];
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
