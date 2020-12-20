#include "tile.hpp"

#include "parsing.hpp"

#include <cassert>


Tile::Tile(const std::vector<std::string> tile) : tile_picture(tile) {
    tile_picture = std::vector<std::string>(tile.begin() + 1, tile.end());
    id = std::stoll(aoc::grab_information(tile[0], "Tile (\\d{4}):")[1]);
    orientation = 0;
    connected_tiles = 0;
    flipped = 0;
    above = {0, 0, 0};
    right = {0, 0, 0};
    below = {0, 0, 0};
    left = {0, 0, 0};

    auto tile_width = tile[1].size();
    top_side = tile[1];
    bottom_side = tile.back();

    for(auto i = 1U; i < tile_width + 1; ++i) {
        right_side.push_back(tile[i].at(tile_width - 1));
    }

    for(auto i = 1U; i < tile_width + 1; ++i) {
        left_side.push_back(tile[i].at(0));
    }
}

bool Tile::already_linked(const Tile other) const {
    if(0 != above.size() && above[0] == other.id) {
        return true;
    }
    if(0 != right.size() && right[0] == other.id) {
        return true;
    }
    if(0 != below.size() && below[0] == other.id) {
        return true;
    }
    if(0 != left.size() && left[0] == other.id) {
        return true;
    }
    return false;
}

uint64_t Tile::fit(const Tile other) {
    if(top_side == other.bottom_side) {
        return 1;
    }

    if(is_fit_right(other)) {
        return 2;
    }

    if(is_fit_below(other)) {
        return 3;
    }

    if(left_side == other.right_side) {
        return 4;
    }
    return 0;
}

bool Tile::is_fit_right(const Tile other) const {
    return right_side == other.left_side;
}

bool Tile::is_fit_below(const Tile other) const {
    return bottom_side == other.top_side;
}

void Tile::piece_together(Tile other, uint64_t spot) {
    connected_tiles++;
    switch(spot) {
        case 1: above[0] = other.id;
                above[1] = other.orientation;
                above[2] = other.flipped;
                break;
        case 2: right[0] = other.id;
                right[1] = other.orientation;
                right[2] = other.flipped;
                break;
        case 3: below[0] = other.id;
                below[1] = other.orientation;
                below[2] = other.flipped;
                break;
        case 4: left[0] = other.id;
                left[1] = other.orientation;
                left[2] = other.flipped;
                break;
        default: return;
    }
}

void Tile::rotate_picture() {
    std::vector<std::string> tmp_picture(tile_picture[0].size());
    for(auto line: tile_picture) {
        std::reverse(line.begin(), line.end());
        for(auto i = 0U; i < tile_picture.size(); ++i) {
            tmp_picture[i].push_back(line.at(i));
        }
    }
}

void Tile::rotate() {
    auto tmp_top_side = top_side;
    top_side = right_side;
    right_side = bottom_side;
    std::reverse(right_side.begin(), right_side.end());
    bottom_side = left_side;
    left_side = tmp_top_side;
    std::reverse(left_side.begin(), left_side.end());
    orientation = (orientation + 90) % 360;

    auto tmp_above = above;
    above = right;
    right = below;
    below = left;
    left = tmp_above;

    rotate_picture();
}

void Tile::flip_picture() {
    for(auto& line: tile_picture) {
        std::reverse(line.begin(), line.end());
    }
}

void Tile::flip() {
    // Flip tile along the y axis
    if(0U == flipped) {
        flipped = 1U;
    } else {
        flipped = 0U;
    }
    std::reverse(top_side.begin(), top_side.end());
    auto tmp = right_side;
    right_side = left_side;
    left_side = tmp;
    std::reverse(bottom_side.begin(), bottom_side.end());
    auto tmp_right = right;
    right = left;
    left = tmp_right;
    flip_picture();
}

uint64_t Tile::get_id() const {
    return id;
}

uint64_t Tile::get_flipped() const {
    return flipped;
}

bool Tile::is_corner_piece() const {
    return is_top_left() || is_top_right() || is_bottom_left() || is_bottom_right();
}

bool Tile::is_top_left() const {
    if(2 != connected_tiles) {
        return false;
    }
    if(above[0] == 0 && right[0] != 0 && below[0] != 0 && left[0] == 0) {
        return true;
    }
    return false;
}

bool Tile::is_top_right() const {
    if(2 != connected_tiles) {
        return false;
    }
    if(above[0] == 0 && right[0] == 0 && below[0] != 0 && left[0] != 0) {
        return true;
    }
    return false;
}

bool Tile::is_bottom_left() const {
    if(2 != connected_tiles) {
        return false;
    }
    if(above[0] != 0 && right[0] != 0 && below[0] == 0 && left[0] == 0) {
        return true;
    }
    return false;
}

bool Tile::is_bottom_right() const {
    if(2 != connected_tiles) {
        return false;
    }
    if(above[0] != 0 && right[0] == 0 && below[0] == 0 && left[0] != 0) {
        return true;
    }
    return false;
}

uint64_t Tile::get_orientation() const {
    return orientation;
}

std::ostream& operator<<(std::ostream& os, const Tile& tile) {
    os << tile.id << ":" << '\n';
    for(auto line: tile.tile_picture) {
        os << line << '\n';
    }
    return os;
}

uint64_t Tile::get_connected_tiles() const {
    return connected_tiles;
}

void Tile::strip_sides() {
    tile_picture.erase(tile_picture.begin());
    tile_picture.erase(tile_picture.end());
    for(auto& line: tile_picture) {
        line.erase(line.begin());
        line.erase(line.end() - 1);
    }
}

bool Tile::has_tile_below() const {
    if(below[0] != 0) {
        return true;
    } else {
        return false;
    }
}

bool Tile::has_right_tile() const {
    return right[0] != 0;
}

std::vector<uint64_t> Tile::get_tile_below() const {
    return below;
}

std::vector<uint64_t> Tile::get_right_tile() const {
    return right;
}

std::vector<uint64_t> Tile::get_tile_above() const {
    return above;
}

std::vector<uint64_t> Tile::get_left_tile() const {
    return left;    
}

std::vector<std::string> Tile::get_picture() const {
    return tile_picture;
}
