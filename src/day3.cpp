#include "days.hpp"

#include <iostream>

#include "aoc_input.hpp"

void day3() {
    const auto input_lines = aoc::read_input_linewise("");
    const auto hill_height = input_lines.size();
    const auto hill_part_width = input_lines[0].length();
    unsigned int position_down = 0;
    unsigned int position_right = 0;
    constexpr unsigned int speed_down = 1;
    constexpr unsigned int speed_right = 3;


    unsigned int tree_counter = 0;
    while(position_down != hill_height) {
        if(input_lines[position_down].at(position_right) == '#') {
            tree_counter++;
        }
        position_down += speed_down;
        position_right += speed_right;
        position_right %= hill_part_width;
    }

    std::cout << tree_counter << std::endl;
}
