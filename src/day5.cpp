#include "days.hpp"

#include <algorithm>
#include <map>
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
    unsigned int current_step = pow_2(path_len);

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

    const auto row = follow_binary_path(row_description, 'B', plane.row_path_len);
    const auto column = follow_binary_path(column_description, 'R', plane.column_path_len);
    return column + 8 * row;
}

static unsigned int identify_empty_seat(std::vector<unsigned int> taken_seats) {
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

    std::vector<unsigned int> found_seats;
    for(auto boarding_pass: input_data) {
        found_seats.push_back(identify_seat_id(boarding_pass, santas_plane));
    }

    return identify_empty_seat(found_seats);
}

/*
Alternative solution, inspired by others, it's only faster than the solution
above if optimizations are turned off. Otherwise binary_seat_search is twice as
fast. Using the std::map with replace is even 3 times slower than binary_seat_search
*/
static unsigned int pass_to_number(std::string& pass) {
    /*
    char r;
    std::map<char, char> replacement_chars = {
        {'F', '0'},
        {'B', '1'},
        {'L', '0'},
        {'R', '1'}};
    std::replace_if(pass.begin(),
            pass.end(),
            [&](char c){return r = replacement_chars[c];},
            r);
    */

    std::replace(pass.begin(), pass.end(), 'F', '0');
    std::replace(pass.begin(), pass.end(), 'B', '1');
    std::replace(pass.begin(), pass.end(), 'L', '0');
    std::replace(pass.begin(), pass.end(), 'R', '1');
    return std::stoi(pass, 0, 2);
}


unsigned int alternative_seat_search(std::vector<std::string> input_data) {
    std::vector<unsigned int> seats;
    std::transform(input_data.begin(), input_data.end(), std::back_inserter(seats), pass_to_number);
    return identify_empty_seat(seats);
}
