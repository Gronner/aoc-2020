#include "days.hpp"

#include<map>
#include<vector>

#include <iostream>

using space_t = std::vector<std::vector<std::vector<bool>>>;
static constexpr auto rounds = 6U + 1U;

uint64_t conways_cubes(std::vector<std::string> input_data) {
/*
    input_data = {
        ".#.",
        "..#",
        "###",
    };
    */
    space_t infinite_space;
    for(auto z = 0U; z < 3U + 2 * rounds; ++z) {
        std::vector<std::vector<bool>> y_space;
        for(auto y = 0U; y < input_data.size() + 2 * rounds; ++y) {
            std::vector<bool> x_space;
            for(auto x = 0U; x < input_data[0].size() + 2 * rounds; ++x) {
                x_space.push_back(false);
            }
            y_space.push_back(x_space);
        }
        infinite_space.push_back(y_space);
    }

    std::vector<int64_t> coordinates = {1 + rounds, 0 + rounds, 0 + rounds}; // z, y, x
    for(auto y_line: input_data) {
        coordinates[2] = 0 + rounds;
        for(auto x_dot: y_line) {
                if('#' == x_dot) {
                    infinite_space[coordinates[0]][coordinates[1]][coordinates[2]] = true;
                }
            coordinates[2]++;
        }
        coordinates[1]++;
    }

    std::cout << "Preevolution" << std::endl;

    for(auto z_plane: infinite_space) {
        for(auto y_plane: z_plane) {
            for(auto x: y_plane) {
                if(true == x) {
                    std::cout << '#';
                } else {
                    std::cout << '.';
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    static const std::vector<std::vector<int64_t>> surrounding_space = {
        {-1, 0, 0}, {-1, 0, -1}, {-1, 1, -1}, {-1, 1, 0}, {-1, 1, 1}, {-1, 0, 1}, {-1, -1, 1}, {-1, -1, 0}, {-1, -1, -1},
                    {0, 0, -1}, {0, 1, -1}, {0, 1, 0}, {0, 1, 1}, {0, 0, 1}, {0, -1, 1}, {0, -1, 0}, {0, -1,-1},
        {1, 0, 0}, {1, 0, -1}, {1, 1, -1}, {1, 1, 0}, {1, 1, 1}, {1, 0, 1}, {1, -1, 1}, {1, -1, 0}, {1, -1, -1}
    };
    for(auto time = 0U; time < (rounds - 1); ++time) {
        space_t future_space = infinite_space;
        for(auto z_plane = 1U; z_plane < infinite_space.size() - 1; ++z_plane) {
            for(auto y_line = 1U; y_line < infinite_space[0].size() - 1; ++y_line) {
                for(auto x = 1U; x < infinite_space[0][0].size() - 1; ++x) {
                    auto neighbors = 0;
                    //std::cout << "Checking " << z_plane << " " << y_line << " " << x << std::endl;
                    for(auto coordinates: surrounding_space) {
                        //std::cout << "Neighbour" << z_plane + coordinates[0] << " " << y_line + coordinates[1] << " " << x + coordinates[2] ;
                        if(true == infinite_space[z_plane + coordinates[0]][y_line + coordinates[1]][x + coordinates[2]]) {
                            //std::cout << " Active";
                            neighbors++;
                        }
                        //std::cout << std::endl;
                    }

                    if(true == infinite_space[z_plane][y_line][x]) {
                        if(2 == neighbors || 3 == neighbors) {

                        } else {
                            //std::cout << "Deactivate" << std::endl;
                            future_space[z_plane][y_line][x] = false;
                        }
                    } else {
                        if(3 == neighbors) {
                            //std::cout << "Activate" << std::endl;
                            future_space[z_plane][y_line][x] = true;
                        }
                    }
                }
            }
        }
        infinite_space = future_space;
    }


    std::cout << "Postevolution" << std::endl;

    auto active_cubes = 0U;
    for(auto z_plane: infinite_space) {
        for(auto y_plane: z_plane) {
            for(auto x: y_plane) {
                if(true == x) {
                    std::cout << '#';
                    active_cubes++;
                } else {
                    std::cout << '.';
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return active_cubes;
}
