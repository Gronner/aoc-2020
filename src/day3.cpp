#include "days.hpp"

#include <iostream>

#include "aoc_input.hpp"

unsigned int sleeding(std::vector<std::string> input_data) {
    constexpr int speed_sets[5][2] = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
    const auto hill_height = input_data.size() - 1;
    const auto hill_part_width = input_data[0].length();

    unsigned int total_tree_count = 0;
    for(auto& speed_set: speed_sets) {
        unsigned int position_down = 0;
        unsigned int position_right = 0;
        unsigned int speed_right = speed_set[0];
        unsigned int speed_down = speed_set[1];


        unsigned int tree_counter = 0;
        while(position_down <= hill_height) {
            if(input_data[position_down].at(position_right) == '#') {
                tree_counter++;
            }
            position_down += speed_down;
            position_right += speed_right;
            position_right %= hill_part_width;
        }

        if(total_tree_count == 0) {
            total_tree_count += tree_counter;
        } else {
            total_tree_count *= tree_counter;
        }
    }

    return total_tree_count;
}
