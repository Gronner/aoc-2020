#include "days.hpp"

#include <algorithm>
#include <vector>

#include <iostream>

struct PlaneLayout {
    const unsigned int row_path_len;
    const unsigned int column_path_len;
};

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

static unsigned int identify_seat_id(const std::string boarding_pass, const PlaneLayout plane) {
    const auto row_description = boarding_pass.substr(0, plane.row_path_len);
    const auto column_description = boarding_pass.substr(7, plane.column_path_len);

    const auto row = follow_binary_path(row_description, 'B', pow_2(plane.row_path_len));
    const auto column = follow_binary_path(column_description, 'R', pow_2(plane.column_path_len));
    return column + 8 * row;
}

static unsigned int identify_empty_seat(std::vector<int> taken_seats) {
    std::sort(taken_seats.begin(), taken_seats.end());
    for(size_t i = 1; i < taken_seats.size(); i++) {
        if(taken_seats[i-1] + 2 == taken_seats[i]) {
            return taken_seats[i] - 1;
        }
    }
    return 0;
}

unsigned int binary_seat_search(const std::vector<std::string> input_data) {
    constexpr PlaneLayout santas_plane = {.row_path_len=7, .column_path_len=3};

    std::vector<int> found_seats;
    for(auto boarding_pass: input_data) {
        found_seats.push_back(identify_seat_id(boarding_pass, santas_plane));
    }

    return identify_empty_seat(found_seats);
}
