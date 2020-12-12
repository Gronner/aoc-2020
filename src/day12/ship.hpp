#pragma once

#include <cstdint>
#include <string>

#include "command.hpp"

struct Position {
    int x;
    int y;
};

class Ship {
    private:
        Position position;
        Position waypoint;
        char direction;
        void move_to_waypoint(int speed);
        void turn_waypoint(NavigationCommand command);
        void move_waypoint(const NavigationCommand command);
    public:
        Ship(Position position=Position(0,0));
        void navigate(const NavigationCommand command);
        uint32_t traveled_distance(Position starting_point=Position(0,0)) const;
};
