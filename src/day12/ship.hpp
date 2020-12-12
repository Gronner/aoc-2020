#pragma once

#include <cstdint>
#include <string>

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
        void turn_waypoint(char turn_direction, int degree);
        void move_waypoint(char move_direction, int distance);
    public:
        Ship(Position position=Position(0,0));
        void navigate(std::string command);
        uint32_t traveled_distance(Position starting_point=Position(0,0)) const;
};
