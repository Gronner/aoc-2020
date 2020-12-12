#include "day12/ship.hpp"

#include <cmath>

#include "parsing.hpp"

Ship::Ship(Position starting_position) : position(starting_position){
    waypoint = Position(10, 1);
    direction = 'E';
}

void Ship::navigate(const std::string command) {
    const auto movement = aoc::grab_information(command, "(\\w)(\\d*)");
    auto command_argument = movement[1].at(0);
    auto command_value = std::stoi(movement[2]);
    switch(command_argument) {
        case 'F': move_to_waypoint(command_value);
                  break;
        case 'L':
        case 'R': turn_waypoint(command_argument, command_value);
                  break;
        default: move_waypoint(command_argument, command_value);
    }
}

void Ship::move_to_waypoint(const int speed) {
    position.x += speed * waypoint.x;
    position.y += speed * waypoint.y;
}

void Ship::turn_waypoint(const char turn_direction, int degree) {
    while(0 != degree) {
        const auto x = waypoint.x;
        const auto y = waypoint.y;
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

void Ship::move_waypoint(const char move_direction, const int distance) {
    switch(move_direction) {
        case 'N': waypoint.y += distance;
                  break;
        case 'E': waypoint.x += distance;
                  break;
        case 'S': waypoint.y -= distance;
                  break;
        case 'W': waypoint.x -= distance;
                  break;
        default: break;
    }
}

uint32_t Ship::traveled_distance(Position starting_point) const {
    return std::abs(position.x - starting_point.x) + std::abs(position.y - starting_point.y);
}
