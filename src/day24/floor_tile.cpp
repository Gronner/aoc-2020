#include "floor_tile.hpp"

#include <cassert>

FloorTile::FloorTile(std::vector<int64_t> coordinates) : color(false), coordinates(coordinates) {
    assert(coordinates[0] + coordinates[1] + coordinates[2] == 0);
}

void FloorTile::flip() {
    color = !color;
}

bool FloorTile::get_color() const {
    return color;
}

std::vector<int64_t> FloorTile::get_coordinates() const {
    return coordinates;
}

std::vector<int64_t> FloorTile::get_neigbour(const std::string direction) const {
    std::vector<int64_t> neighbour_coordinates{0, 0, 0}; // x, y,z 
    if("e" == direction) {
        neighbour_coordinates[0] = coordinates[0] + 1;
        neighbour_coordinates[1] = coordinates[1] - 1;
        neighbour_coordinates[2] = coordinates[2];
    } else if("se" == direction) {
        neighbour_coordinates[0] = coordinates[0];
        neighbour_coordinates[1] = coordinates[1] - 1;
        neighbour_coordinates[2] = coordinates[2] + 1;
    } else if("sw" == direction) {
        neighbour_coordinates[0] = coordinates[0] - 1;
        neighbour_coordinates[1] = coordinates[1];
        neighbour_coordinates[2] = coordinates[2] + 1;
    } else if("w" == direction) {
        neighbour_coordinates[0] = coordinates[0] - 1;
        neighbour_coordinates[1] = coordinates[1] + 1;
        neighbour_coordinates[2] = coordinates[2];
    } else if("nw" == direction) {
        neighbour_coordinates[0] = coordinates[0];
        neighbour_coordinates[1] = coordinates[1] + 1;
        neighbour_coordinates[2] = coordinates[2] - 1;
    } else if("ne" == direction) {
        neighbour_coordinates[0] = coordinates[0] + 1;
        neighbour_coordinates[1] = coordinates[1];
        neighbour_coordinates[2] = coordinates[2] - 1;
    } else {
        return neighbour_coordinates;
    }
    assert(neighbour_coordinates[0] + neighbour_coordinates[1] + neighbour_coordinates[2] == 0);
    return neighbour_coordinates;
}
