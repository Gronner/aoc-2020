#include "days.hpp"

#include "tile.hpp"

#include <cassert>
#include <iostream>

static void flip_picture(std::vector<std::string>& picture) {
    for(auto& line: picture) {
        std::reverse(line.begin(), line.end());
    }
}

static void rotate_picture(std::vector<std::string>& picture) {
    std::vector<std::string> tmp_picture(picture[0].size());
    for(auto line: picture) {
        std::reverse(line.begin(), line.end());
        for(auto i = 0U; i < picture.size(); ++i) {
            tmp_picture[i].push_back(line.at(i));
        }
    }
    picture = tmp_picture;
}

uint64_t solve_day20(input_t input_data) {
    input_data = {
        "Tile 2311:",
        "..##.#..#.",
        "##..#.....",
        "#...##..#.",
        "####.#...#",
        "##.##.###.",
        "##...#.###",
        ".#.#.#..##",
        "..#....#..",
        "###...#.#.",
        "..###..###",
        "",
        "Tile 1951:",
        "#.##...##.",
        "#.####...#",
        ".....#..##",
        "#...######",
        ".##.#....#",
        ".###.#####",
        "###.##.##.",
        ".###....#.",
        "..#.#..#.#",
        "#...##.#..",
        "",
        "Tile 1171:",
        "####...##.",
        "#..##.#..#",
        "##.#..#.#.",
        ".###.####.",
        "..###.####",
        ".##....##.",
        ".#...####.",
        "#.##.####.",
        "####..#...",
        ".....##...",
        "",
        "Tile 1427:",
        "###.##.#..",
        ".#..#.##..",
        ".#.##.#..#",
        "#.#.#.##.#",
        "....#...##",
        "...##..##.",
        "...#.#####",
        ".#.####.#.",
        "..#..###.#",
        "..##.#..#.",
        "",
        "Tile 1489:",
        "##.#.#....",
        "..##...#..",
        ".##..##...",
        "..#...#...",
        "#####...#.",
        "#..#.#.#.#",
        "...#.#.#..",
        "##.#...##.",
        "..##.##.##",
        "###.##.#..",
        "",
        "Tile 2473:",
        "#....####.",
        "#..#.##...",
        "#.##..#...",
        "######.#.#",
        ".#...#.#.#",
        ".#########",
        ".###.#..#.",
        "########.#",
        "##...##.#.",
        "..###.#.#.",
        "",
        "Tile 2971:",
        "..#.#....#",
        "#...###...",
        "#.#.###...",
        "##.##..#..",
        ".#####..##",
        ".#..####.#",
        "#..#.#..#.",
        "..####.###",
        "..#.#.###.",
        "...#.#.#.#",
        "",
        "Tile 2729:",
        "...#.#.#.#",
        "####.#....",
        "..#.#.....",
        "....#..#.#",
        ".##..##.#.",
        ".#.####...",
        "####.#.#..",
        "##.####...",
        "##..#.##..",
        "#.##...##.",
        "",
        "Tile 3079:",
        "#.#.#####.",
        ".#..######",
        "..#.......",
        "######....",
        "####.#..#.",
        ".#...#.##.",
        "#.#####.##",
        "..#.###...",
        "..#.......",
        "..#.###...",
        "",
    };
    auto start_of_current_tile = input_data.begin();
    std::vector<Tile> tiles;
    for(auto line = input_data.begin(); line != input_data.end(); ++line) {
        if("" != *line) {
            continue;
        }
        auto tile = Tile(std::vector<std::string>(start_of_current_tile, line));
        tiles.push_back(tile);
        start_of_current_tile = line + 1;
    }

    for(auto& tile: tiles) {
        for(auto other: tiles) {
            if(tile.get_id() == other.get_id()) {
                continue;
            }
            for(auto j = 0; j < 2; ++j) {
                auto found = false;
                for(auto i = 0; i < 4; ++i) {
                    auto spot = tile.fit(other);
                    if(0 != spot) {
                        tile.piece_together(other, spot);
                        found = true;
                        break;
                    }
                    other.rotate();
                }
                if(found) {
                    break;
                }
                other.flip();
            }
        }
    }

    uint64_t product = 1;
    for(auto tile: tiles) {
        if(tile.is_corner_piece()) {
            product *= tile.get_id();
        }
    }

    assert(20899048083289 == product);
    // assert(20033377297069 == product);
    
    for(auto tile: tiles) {
        if(tile.get_id() != 1951 && tile.get_id() != 2311 && tile.get_id() != 3079) {
            continue;
        }
        std::cout << tile.get_id() << " Flipped: " << tile.get_flipped() << " Orientation: " << tile.get_orientation() << std::endl;
        std::cout << "Above: ";
        for(auto i: tile.get_tile_above()) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        std::cout << "Right: ";
        for(auto i: tile.get_right_tile()) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        std::cout << "Below: ";
        for(auto i: tile.get_tile_below()) {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        std::cout << "Left: ";
        for(auto i: tile.get_left_tile()) {
            std::cout << i << " ";
        }
        std::cout << '\n' << std::endl;
    }

    uint64_t top_left_id = 0;
    for(auto& tile: tiles) {
        tile.strip_sides();
        if(tile.is_top_left()) {
            top_left_id = tile.get_id();
        }
    }
    auto current_tile = *std::find_if(tiles.begin(), tiles.end(), [&top_left_id](const Tile& tile) {return tile.get_id() == top_left_id;});
    std::vector<std::vector<Tile>> sea_map;
    do {
        std::vector<Tile> longitude;
        auto tile_below_information = current_tile.get_tile_below();
        do {
            longitude.push_back(current_tile);
            auto right_tile_information = current_tile.get_right_tile();
            current_tile = *std::find_if(tiles.begin(), tiles.end(), [&right_tile_information](const Tile& tile) {return tile.get_id() == right_tile_information[0];});

            //std::cout << current_tile.get_id() << std::endl;
            if(current_tile.get_flipped() != right_tile_information[2]) {
                //std::cout << "Flip" << std::endl;
                current_tile.flip();
            }
            while(right_tile_information[1] != current_tile.get_orientation()) {
                //std::cout << "Rotate" << std::endl;
                current_tile.rotate();
            }
        } while(current_tile.has_right_tile());
        longitude.push_back(current_tile);
        sea_map.push_back(longitude);

        current_tile = *std::find_if(tiles.begin(), tiles.end(), [&tile_below_information](const Tile& tile) {return tile.get_id() == tile_below_information[0];});
        //std::cout << current_tile.get_id() << std::endl;
        if(current_tile.get_flipped() != tile_below_information[2]) {
            //std::cout << "Flip" << std::endl;
            current_tile.flip();
        }
        while(tile_below_information[1] != current_tile.get_orientation()) {
            //std::cout << "Rotate" << std::endl;
            current_tile.rotate();
        }

    } while(current_tile.has_tile_below());

    std::vector<Tile> longitude;
    std::vector<uint64_t> visited_ids;
    do {
        longitude.push_back(current_tile);
        visited_ids.push_back(current_tile.get_id());
        auto right_tile_information = current_tile.get_right_tile();
        current_tile = *std::find_if(tiles.begin(), tiles.end(), [&right_tile_information](const Tile& tile) {return tile.get_id() == right_tile_information[0];});
        //std::cout << current_tile.get_id() << std::endl;
        if(current_tile.get_flipped() != right_tile_information[2]) {
            //std::cout << "Flip" << std::endl;
            current_tile.flip();
        }
        while(right_tile_information[1] != current_tile.get_orientation()) {
            //std::cout << "Rotate" << std::endl;
            current_tile.rotate();
        }
    } while(std::find(visited_ids.begin(), visited_ids.end(), current_tile.get_id()) == visited_ids.end());
    sea_map.push_back(longitude);

    //std::cout << std::endl;
    std::vector<std::string> sea_picture(sea_map.size() * 8);
    auto longitude_count = 0;
    for(auto longitude: sea_map) {
        for(auto tile: longitude) {
            auto row_count= 0;
            for(auto row: tile.get_picture()) {
                sea_picture[longitude_count * 8 + row_count] += row;
                row_count++;
            }
        }
        longitude_count++;
    }
    flip_picture(sea_picture);
    rotate_picture(sea_picture);
    rotate_picture(sea_picture);

    for(auto& line: sea_picture) {
        line.insert(line.begin() + 8, ' ');
        line.insert(line.begin() + 17, ' ');
    }

    sea_picture.insert(sea_picture.begin() + 8, " ");
    sea_picture.insert(sea_picture.begin() + 17, " ");

    for(auto line: sea_picture) {
        std::cout << line << std::endl;
    }

    uint64_t not_a_monster = 0;

    return not_a_monster;
}
