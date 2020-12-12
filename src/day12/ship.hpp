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
        std::vector<char> turn_table{'E', 'S', 'W', 'N'};
        void move_to_waypoint(int speed);
        void turn_waypoint(NavigationCommand command);
        void move_waypoint(const NavigationCommand command);
        void turn(const NavigationCommand);
        void move(const NavigationCommand);
    public:
        Ship(Position position=Position(0,0));
        void navigate(const NavigationCommand command);
        void drive(const NavigationCommand command);
        uint32_t traveled_distance(Position starting_point=Position(0,0)) const;
};
