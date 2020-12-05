#include "days.hpp"

#include <numeric>
#include <vector>

#include <iostream>

unsigned int binary_set_search(const std::vector<std::string> input_data) {
    int max_seat = 0;
    int seat_number = 0;

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
        seat_number = column + 8 * row;
        if(seat_number > max_seat) {
            max_seat = seat_number;
        }
    }
    return max_seat;
}
