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

static auto parse_tiles(const input_t input_data) {
    std::vector<Tile> tiles;
    auto start_of_current_tile = input_data.begin();
    for(auto line = input_data.begin(); line != input_data.end(); ++line) {
        if("" != *line) {
            continue;
        }
        auto tile = Tile(std::vector<std::string>(start_of_current_tile, line));
        tiles.push_back(tile);
        start_of_current_tile = line + 1;
    }
    return tiles;
}

static void connect_tiles(std::vector<Tile>& tiles) {
    for(auto& tile: tiles) {
        for(auto other: tiles) {
            std::cout << tile.get_id() << " to " << other.get_id() << std::endl;
            std::cout << tile.get_orientation() << " " << tile.get_flipped() << std::endl;
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
                    std::cout << "Rotate" << std::endl;
                    other.rotate();
                }
                if(found) {
                    break;
                }
                std::cout << "Flip" << std::endl;
                other.flip();
            }
            std::cout << tile.get_orientation() << " " << tile.get_flipped() << std::endl;
            std::cout << other.get_id() << " " << other.get_orientation() << " " << other.get_flipped() << std::endl;
        }
    }
}

static uint64_t compute_corner_product(const std::vector<Tile> tiles) {
    uint64_t product = 1;
    for(auto tile: tiles) {
        if(tile.is_corner_piece()) {
            product *= tile.get_id();
        }
    }
    return product;
}

static Tile find_tile(const std::vector<Tile> tiles, const uint64_t id) {
    auto tile = std::find_if(tiles.begin(), tiles.end(), [&id](const Tile& tile) {return tile.get_id() == id;});
    assert(tile != tiles.end());
    return *tile;
}

#pragma GCC diagnostic ignored "-Wunused-function"
static void print_tile_information(const std::vector<Tile> tiles, const uint64_t id) {
    auto tile = find_tile(tiles, id);
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

static Tile find_top_left_corner(const std::vector<Tile> tiles) {
    uint64_t top_left_id = 0;
    for(auto& tile: tiles) {
        if(tile.is_top_left()) {
            top_left_id = tile.get_id();
        }
    }
    return find_tile(tiles, top_left_id);
}

static void turn_to_fit(Tile& tile, const uint64_t flipped, const uint64_t orientation) {
    std::cout << tile.get_id() << std::endl;
    std::cout << "Should: " << flipped << " Is: " << tile.get_flipped() << std::endl;
    while(flipped != tile.get_flipped()) {
        tile.flip();
    }
    std::cout << "Should: " << flipped << " Is: " << tile.get_flipped() << std::endl;
    std::cout << "Should: " << orientation << " Is: " << tile.get_orientation() << std::endl;
    while(orientation != tile.get_orientation()) {
        tile.rotate();
    }
    std::cout << "Should: " << orientation << " Is: " << tile.get_orientation() << std::endl;
}

static std::vector<Tile> build_longitude(const std::vector<Tile> tiles, Tile current_tile) {
    std::vector<Tile> longitude;
    longitude.push_back(current_tile);
    while(current_tile.has_right_tile()) {
        const auto right_tile_info = current_tile.get_right_tile();
        assert(right_tile_info[0] != 0U);
        assert(right_tile_info[1] % 90U == 0U && right_tile_info[1] < 360U);
        assert(right_tile_info[2] == 1U || right_tile_info[2] == 0U);
        auto next_tile = find_tile(tiles, right_tile_info[0]);
        turn_to_fit(next_tile, right_tile_info[2], right_tile_info[1]);

        assert(current_tile.is_fit_right(next_tile));

        longitude.push_back(next_tile);
        current_tile = next_tile;
    }
    return longitude;
}

static Tile get_next_tile_below(const std::vector<Tile> tiles, const uint64_t id, const uint64_t flipped, const uint64_t orientation) {
    assert(id != 0);
    assert(flipped == 1U || flipped == 0U);
    assert(orientation % 90U == 0U && orientation < 360U);
    auto next_tile = find_tile(tiles, id);
    turn_to_fit(next_tile, flipped, orientation);
    return next_tile;
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
    auto tiles = parse_tiles(input_data);
    connect_tiles(tiles);
    const auto product = compute_corner_product(tiles);


    assert(20899048083289 == product);
    // assert(20033377297069 == product);
    std::cout << "\nPart 1 finished\n" << std::endl;
    
    for(auto& tile: tiles) {
        tile.strip_sides();
    }


    auto current_tile = find_top_left_corner(tiles);
    assert(2971 == current_tile.get_id());

    std::vector<std::vector<Tile>> sea_map;
    std::vector<Tile> visited;
    while(current_tile.has_tile_below()) {
        auto next_tile_below_information = current_tile.get_tile_below();
        auto longitude = build_longitude(tiles, current_tile);
        sea_map.push_back(longitude);

        auto next_tile_below = get_next_tile_below(tiles,
                                                   next_tile_below_information[0],
                                                   next_tile_below_information[2],
                                                   next_tile_below_information[1]);
        assert(current_tile.is_fit_below(next_tile_below));
        current_tile = next_tile_below;
    }
    auto longitude = build_longitude(tiles, current_tile);
    sea_map.push_back(longitude);

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

    std::cout << std::endl;
    for(auto line: sea_picture) {
        std::cout << line << std::endl;
    }

    uint64_t not_a_monster = 0;

    return not_a_monster;
}
