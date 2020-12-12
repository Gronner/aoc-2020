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


void move_to_waypoint(Ship& ferry, const Ship waypoint, const int speed) {
    ferry.x += speed * waypoint.x;
    ferry.y += speed * waypoint.y;
}

void turn(Ship& waypoint, const char turn_direction, int degree) {
    while(0 != degree) {
        auto x = waypoint.x;
        auto y = waypoint.y;
        degree -= 90;
        if('R' == turn_direction) {
            waypoint.x = y;
            waypoint.y = -x;
        } else {
            waypoint.x = -y;
            waypoint.y = x;
        }
    }
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
    Ship waypoint {10, 1 , 'E'};

    for(const auto movement: navigation_movements) {
        switch(movement.first) {
            case 'F': move_to_waypoint(ferry, waypoint, movement.second);
                      break;
            case 'L': 
            case 'R': turn(waypoint, movement.first, movement.second);
                      break;
            default: move_direction(waypoint, movement.first, movement.second);
        }
        std::cout << "Command:" << movement.first << movement.second <<std::endl;
        std::cout << "Waypoint:" << waypoint.x << " " << waypoint.y << std::endl;
        std::cout << "Ferry:" << ferry.x << " " << ferry.y << std::endl;
        std::cout << std::endl;
    }

    return compute_manhatten_distance(ferry);
}
