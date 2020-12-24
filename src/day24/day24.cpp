#include "days.hpp"

#include <algorithm>
#include <map>
#include <vector>

#include "day24/floor_tile.hpp"

using floor_t = std::map<std::vector<int64_t>, FloorTile>;

uint64_t solve_day24(input_t input_data) {
    std::vector<std::vector<std::string>> movements;
    static const std::vector<std::string> tokens = {"e", "se", "sw", "w", "nw", "ne"};
    for(auto line: input_data) {
        std::vector<std::string> movement;
        while(!line.empty()) {
            if(tokens.end() != std::find(tokens.begin(), tokens.end(), line.substr(0, 1))) {
                movement.push_back(line.substr(0, 1));
                line.erase(line.begin(), line.begin() + 1);
            } else {
                movement.push_back(line.substr(0, 2));
                line.erase(line.begin(), line.begin() + 2);
            }
        }
        movements.push_back(movement);
    }

    floor_t floor;
    const std::vector<int64_t> current_coordinates {0, 0, 0};
    const FloorTile ref_tile(current_coordinates);
    floor.insert(std::make_pair(current_coordinates, ref_tile));

    for(const auto movement: movements) {
        auto current_tile = ref_tile;
        for(const auto move: movement) {
            auto next_coordinates = current_tile.get_neigbour(move);
            if(floor.contains(next_coordinates)) {
                current_tile = (*floor.find(next_coordinates)).second;
            } else {
                current_tile = FloorTile(next_coordinates);
                floor.insert(std::make_pair(next_coordinates, current_tile));
            }
        }
        current_tile.flip();
        floor.at(current_tile.get_coordinates()) = current_tile;
    }

    auto count = 0;
    auto cleared_floor = floor;
    for(auto tile: floor) {
        if(tile.second.get_color()) {
            count++;
        } else {
            cleared_floor.erase(tile.first);
        }
    }
    floor = cleared_floor;

    for(auto i = 0; i < 100; ++i) {
        // Find neighbours
        auto neighbour_floor = floor;
        for(auto tile: floor) {
            for(auto direction: tokens) {
                auto neighbour_coordinates = tile.second.get_neigbour(direction);
                if(!neighbour_floor.contains(neighbour_coordinates)) {
                    FloorTile neighbour_tile(neighbour_coordinates);
                    neighbour_floor.insert(std::make_pair(neighbour_coordinates,
                                                          neighbour_tile));
                }
            }
        }
        floor = neighbour_floor;

        // Perform evolution
        floor_t next_floor; 
        for(auto tile: floor) {
            auto neighbour_count = 0;
            for(const auto direction: tokens) {
                const auto neighbour_coordinates = tile.second.get_neigbour(direction);
                if(floor.contains(neighbour_coordinates) && (*floor.find(neighbour_coordinates)).second.get_color()) {
                    neighbour_count++;
                }
            }
            if(tile.second.get_color()) {
                if(neighbour_count == 1 || neighbour_count == 2) {
                    next_floor.insert(std::make_pair(tile.second.get_coordinates(), tile.second));
                }
            } else {
                if(2 == neighbour_count) {
                    tile.second.flip();
                    next_floor.insert(std::make_pair(tile.second.get_coordinates(), tile.second));
                }
            }
        }
        floor = next_floor;
    }
    return floor.size();
}
