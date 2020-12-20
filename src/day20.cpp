#include "days.hpp"

#include "tile.hpp"

#include <iostream>

uint64_t solve_day20(input_t input_data) {
    /*
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
    */
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
            if(tile.already_linked(other)) {
                continue;
            }
            std::cout << tile.get_id() << " + " << other.get_id() << std::endl;
            for(auto j = 0; j < 2; ++j) {
                auto found = false;
                for(auto i = 0; i < 4; ++i) {
                    if(tile.orient_edges(other)) {
                        std::cout << "Fit" << std::endl;
                        found = true;
                        break;
                    }
                    std::cout << "Rotate" << std::endl;
                    other.rotate();
                }
                if(found) {
                    break;
                }
                std::cout << "Flip" << std::endl;
                other.flip();
            }
        }
    }

    uint64_t product = 1;
    for(auto tile: tiles) {
        if(2 == tile.get_connected_tiles()) {
            std::cout << tile.get_id() << std::endl;
            product *= tile.get_id();
        }
    }

    return product;
}
