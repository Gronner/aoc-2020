#include "days.hpp"

#include "day20/tile.hpp"

#include <cassert>

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
    return *tile;
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

static void turn_to_fit(Tile& next, const Tile current, bool right) {
    auto enumerate = 1U;
    auto is_fit = right ? current.is_fit_right(next) : current.is_fit_below(next);
    while(!is_fit) {
        next.rotate();
        if(4 == enumerate) {
            next.flip();
        }
        enumerate++;
        is_fit = right ? current.is_fit_right(next) : current.is_fit_below(next);
    }
}

static std::vector<Tile> build_longitude(const std::vector<Tile> tiles, Tile current_tile) {
    std::vector<Tile> longitude;
    longitude.push_back(current_tile);
    while(current_tile.has_right_tile()) {
        const auto right_tile_id = current_tile.get_right_tile();
        auto next_tile = find_tile(tiles, right_tile_id);
        turn_to_fit(next_tile, current_tile, true);


        longitude.push_back(next_tile);
        current_tile = next_tile;
    }
    return longitude;
}

static Tile get_next_tile_below(const std::vector<Tile> tiles, uint64_t id, Tile current_tile) {
    auto next_tile = find_tile(tiles, id);
    turn_to_fit(next_tile, current_tile, false);
    return next_tile;
}

static std::vector<std::vector<uint64_t>> get_positions(const std::vector<std::string> monster, char look='#') {
    std::vector<std::vector<uint64_t>> monster_position;
    for(auto line: monster) {
        std::vector<uint64_t> positions;
        for(auto i = 0U; i < line.size(); ++i) {
            if(look == line.at(i)) {
                positions.push_back(i);
            }
        }
        monster_position.push_back(positions);
    }
    return monster_position;
}

static bool check_bodypart(const std::string input, const std::vector<uint64_t> bodypart) {
    for(auto pos: bodypart) {
        if('#' != input.at(pos)) {
            return false;
        }
    }
    return true;
}

static uint64_t find_monster(std::vector<std::string> sea_picture) {
    static const std::vector<std::string> monster = {
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   ",
    };
    static const auto monster_position = get_positions(monster);

    uint64_t monster_count = 0;
    for(auto line = 0U; (line + 2) < sea_picture.size(); ++line) {
        for(auto start = 0U; (start + monster[0].size()) != sea_picture[line].size(); ++start) {
            auto top = check_bodypart(sea_picture[line].substr(start, monster[0].size()), monster_position[0]);
            auto mid = check_bodypart(sea_picture[line + 1].substr(start, monster[1].size()), monster_position[1]);
            auto bot = check_bodypart(sea_picture[line + 2].substr(start, monster[2].size()), monster_position[2]);
            if(top && mid && bot) {
                monster_count++;
            }
        }
    }
    return monster_count;
}


static void kill_bodyparts(std::string& line, std::vector<uint64_t> positions, uint64_t offset) {
    for(auto pos: positions) {
        line[pos + offset] = 'O';
    }
}

static void kill_the_monsters(std::vector<std::string>& sea_picture) {
    static const std::vector<std::string> monster = {
        "                  O ",
        "O    OO    OO    OOO",
        " O  O  O  O  O  O   ",
    };
    static const auto monster_position = get_positions(monster, 'O');

    for(auto line = 0U; (line + 2) < sea_picture.size(); ++line) {
        for(auto start = 0U; (start + monster[0].size()) != sea_picture[line].size(); ++start) {
            auto top = check_bodypart(sea_picture[line].substr(start, monster[0].size()), monster_position[0]);
            auto mid = check_bodypart(sea_picture[line + 1].substr(start, monster[1].size()), monster_position[1]);
            auto bot = check_bodypart(sea_picture[line + 2].substr(start, monster[2].size()), monster_position[2]);
            if(top && mid && bot) {
                kill_bodyparts(sea_picture[line], monster_position[0], start);
                kill_bodyparts(sea_picture[line + 1], monster_position[1], start);
                kill_bodyparts(sea_picture[line + 2], monster_position[2], start);
            }
        }
    }
}

uint64_t solve_day20(input_t input_data) {
    auto tiles = parse_tiles(input_data);
    connect_tiles(tiles);
    const auto product = compute_corner_product(tiles);

    assert(20033377297069 == product);
    
    for(auto& tile: tiles) {
        tile.strip_sides();
    }


    auto current_tile = find_top_left_corner(tiles);

    std::vector<std::vector<Tile>> sea_map;
    std::vector<Tile> visited;
    while(current_tile.has_tile_below()) {
        auto next_tile_id = current_tile.get_tile_below();
        auto longitude = build_longitude(tiles, current_tile);
        sea_map.push_back(longitude);

        auto next_tile_below = get_next_tile_below(tiles,
                                                   next_tile_id,
                                                   current_tile);
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
    uint64_t monster_count = 0;
    uint64_t enumerate = 0;
    while(1) {
        monster_count = find_monster(sea_picture);
        if(monster_count != 0) {
            break;
        }
        rotate_picture(sea_picture);
        enumerate++;
        if(enumerate == 4) {
            flip_picture(sea_picture);
        } 
        if(enumerate == 8) {
            break;
        }
    }
    kill_the_monsters(sea_picture);

    auto rough_sea_count = 0;
    for(auto line: sea_picture) {
        for(auto c: line) {
            if('#' == c) {
                rough_sea_count++;
            }
        }
    }
    return rough_sea_count;
}
