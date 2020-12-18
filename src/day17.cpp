#include "days.hpp"

#include<map>
#include<vector>

#include <iostream>

using space_t = std::vector<std::vector<std::vector<std::vector<bool>>>>;
static constexpr auto rounds = 6U + 1U;

uint64_t conways_cubes(input_t input_data) {
    space_t infinite_space;
    for(auto w = 0U; w < 3U + 2 * rounds; ++w){
        std::vector<std::vector<std::vector<bool>>> z_space;
        for(auto z = 0U; z < 3U + 2 * rounds; ++z) {
            std::vector<std::vector<bool>> y_space;
            for(auto y = 0U; y < input_data.size() + 2 * rounds; ++y) {
                std::vector<bool> x_space;
                for(auto x = 0U; x < input_data[0].size() + 2 * rounds; ++x) {
                    x_space.push_back(false);
                }
                y_space.push_back(x_space);
            }
            z_space.push_back(y_space);
        }
        infinite_space.push_back(z_space);
    }

    std::vector<int64_t> coordinates = {1 + rounds, 1 + rounds, 0 + rounds, 0 + rounds}; // w, z, y, x
    for(auto y_line: input_data) {
        coordinates[3] = 0 + rounds;
        for(auto x_dot: y_line) {
                if('#' == x_dot) {
                    infinite_space[coordinates[0]][coordinates[1]][coordinates[2]][coordinates[3]] = true;
                }
            coordinates[3]++;
        }
        coordinates[2]++;
    }

    std::vector<std::vector<int64_t>> surrounding_space;
    for(auto w = -1; w <= 1; ++w) {
        for(auto z = -1; z <= 1; ++z) {
            for(auto y = -1; y <= 1; ++y) {
                for(auto x = -1; x <= 1; ++x) {
                    if(w == 0 && z == 0 && y == 0 && x == 0) {
                        continue;
                    }
                    surrounding_space.push_back({w, z, y, x});
                }
            }
        }
    }

    for(auto time = 0U; time < (rounds - 1); ++time) {
        space_t future_space = infinite_space;
        for(auto w_plane = 1U; w_plane < infinite_space.size() - 1; ++w_plane) {
            for(auto z_plane = 1U; z_plane < infinite_space[0].size() - 1; ++z_plane) {
                for(auto y_line = 1U; y_line < infinite_space[0][0].size() - 1; ++y_line) {
                    for(auto x = 1U; x < infinite_space[0][0][0].size() - 1; ++x) {
                        auto neighbors = 0;
                        for(auto coordinates: surrounding_space) {
                            if(true == infinite_space[w_plane + coordinates[0]][z_plane + coordinates[1]][y_line + coordinates[2]][x + coordinates[3]]) {
                                neighbors++;
                            }
                        }

                        if(true == infinite_space[w_plane][z_plane][y_line][x]) {
                            if(2 == neighbors || 3 == neighbors) {

                            } else {
                                future_space[w_plane][z_plane][y_line][x] = false;
                            }
                        } else {
                            if(3 == neighbors) {
                                future_space[w_plane][z_plane][y_line][x] = true;
                            }
                        }
                    }
                }
            }
        }
        infinite_space = future_space;
    }


    auto active_cubes = 0U;
    for(auto w_plane: infinite_space) {
        for(auto z_plane: w_plane) {
            for(auto y_plane: z_plane) {
                for(auto x: y_plane) {
                    if(true == x) {
                        active_cubes++;
                    } 
                }
            }
        }
    }

    return active_cubes;
}
