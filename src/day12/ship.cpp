#include "day12/ship.hpp"

#include <algorithm>
#include <cmath>

Ship::Ship(Position starting_position) : position(starting_position){
    waypoint = Position{10, 1};
    direction = 'E';
}

void Ship::navigate(const NavigationCommand command) {
    switch(command.argument) {
        case 'F': move_to_waypoint(command.value);
                  break;
        case 'L':
        case 'R': turn_waypoint(command);
                  break;
        default: move_waypoint(command);
    }
}


void Ship::move_to_waypoint(const int speed) {
    position.x += speed * waypoint.x;
    position.y += speed * waypoint.y;
}

void Ship::turn_waypoint(NavigationCommand command) {
    while(0 != command.value) {
        const auto x = waypoint.x;
        const auto y = waypoint.y;
        command.value -= 90;
        if('R' == command.argument) {
            waypoint.x = y;
            waypoint.y = -x;
        } else {
            waypoint.x = -y;
            waypoint.y = x;
        }
    }
}

void Ship::move_waypoint(const NavigationCommand command) {
    switch(command.argument) {
        case 'N': waypoint.y += command.value;
                  break;
        case 'E': waypoint.x += command.value;
                  break;
        case 'S': waypoint.y -= command.value;
                  break;
        case 'W': waypoint.x -= command.value;
                  break;
        default: break;
    }
}

void Ship::drive(const NavigationCommand command) {
    switch(command.argument) {
        case 'F': move(NavigationCommand{direction, command.value});
                  break;
        case 'L':
        case 'R': turn(command);
                  break;
        default: move(command);
    }
}

void Ship::turn(const NavigationCommand command) {
    const auto rotations = (command.value / 90) % 4;
    if('R' == command.argument) {
        std::rotate(turn_table.begin(), turn_table.begin() + rotations, turn_table.end());
    } else {
        std::rotate(turn_table.rbegin(), turn_table.rbegin() + rotations, turn_table.rend());
    }
    direction = turn_table[0];
}

void Ship::move(const NavigationCommand command) {
    switch(command.argument) {
        case 'N': position.y += command.value;
                  break;
        case 'E': position.x += command.value;
                  break;
        case 'S': position.y -= command.value;
                  break;
        case 'W': position.x -= command.value;
                  break;
        default: break;
    }
}

uint32_t Ship::traveled_distance(Position starting_point) const {
    return std::abs(position.x - starting_point.x) + std::abs(position.y - starting_point.y);
}
