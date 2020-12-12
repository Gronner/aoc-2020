#include "days.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "parsing.hpp"

using NavigationMovement = std::vector<std::pair<char, int>>;

struct Ship {
    int x;
    int y;
    char direction;
};

void move_direction(Ship& ferry, const char direction, const int speed) {
    switch(direction) {
        case 'N': ferry.y += speed;
                  break;
        case 'E': ferry.x += speed;
                  break;
        case 'S': ferry.y -= speed;
                  break;
        case 'W': ferry.x -= speed;
                  break;
        default: break;
    }

}


void turn(Ship& ferry, const char turn_direction, int degree) {
    static const std::vector<char> turn_tables = {'N', 'E', 'S', 'W'};
    auto current_table_entry = std::find(turn_tables.begin(), turn_tables.end(), ferry.direction);
    while(0 != degree) {
        degree -= 90;
        if('R' == turn_direction) {
            current_table_entry++;
            if(current_table_entry == turn_tables.end()) {
                current_table_entry = turn_tables.begin();
            }
        } else {
            if(current_table_entry == turn_tables.begin()) {
                current_table_entry = turn_tables.end();
            }
            current_table_entry--;
        }
    }
    ferry.direction = *current_table_entry;
}

unsigned int compute_manhatten_distance(Ship ferry) {
    return std::abs(ferry.x) + std::abs(ferry.y);
}

unsigned int stormy_navigation(std::vector<std::string> input_data) {
    NavigationMovement navigation_movements;
    for(const auto line: input_data) {
        const auto movement = aoc::grab_information(line, "(\\w)(\\d*)");
        navigation_movements.push_back(std::make_pair(movement[1].at(0), std::stoi(movement[2])));
    } 
    Ship ferry = {0, 0, 'E'};

    for(const auto movement: navigation_movements) {
        switch(movement.first) {
            case 'F': move_direction(ferry, ferry.direction, movement.second);
                      break;
            case 'L': 
            case 'R': turn(ferry, movement.first, movement.second);
                      break;
            default: move_direction(ferry, movement.first, movement.second);
        }
    }

    return compute_manhatten_distance(ferry);
}
