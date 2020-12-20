#include "tile.hpp"

#include "parsing.hpp"


Tile::Tile(std::vector<std::string> tile) : tile_picture(tile) {
    id = std::stoll(aoc::grab_information(tile[0], "Tile (\\d{4}):")[1]);
    orientation = 0;
    connected_tiles = 0;
    above = 0;
    right = 0;
    below = 0;
    left = 0;

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
    if(above == other.id) {
        return true;
    }
    if(right == other.id) {
        return true;
    }
    if(below == other.id) {
        return true;
    }
    if(left == other.id) {
        return true;
    }
    return false;
}

bool Tile::orient_edges(Tile& other) {
    if(top_side == other.bottom_side) {
        above = other.id;
        other.below = id;
        connected_tiles++;
        return true;
    }

    if(right_side == other.left_side) {
        right = other.id;
        other.left = id;
        connected_tiles++;
        return true;
    }

    if(bottom_side == other.top_side) {
        below = other.id;
        other.above= id;
        connected_tiles++;
        return true;
    }

    if(left_side == other.right_side) {
        left = other.id;
        other.right = id;
        connected_tiles++;
        return true;
    }
    return false;
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
}

void Tile::flip() {
    // Flip tile along the y axis
    flipped = !flipped;
    std::reverse(top_side.begin(), top_side.end());
    auto tmp = right_side;
    right_side = left_side;
    left_side = tmp;
    std::reverse(bottom_side.begin(), bottom_side.end());
}

uint64_t Tile::get_id() const {
    return id;
}

bool Tile::is_corner_piece() const {
    return is_top_left() || is_top_right() || is_bottom_left() || is_bottom_right();
}

void Tile::clear_state() {
    above = 0;
    right = 0;
    below = 0;
    left = 0;
    while(0 != orientation) {
        rotate();
    }
    if(flipped) {
        flip();
    }
    connected_tiles = 0;
}

bool Tile::is_top_left() const {
    if(2 != connected_tiles) {
        return false;
    }
    if(above == 0 && right != 0 && below != 0 && left == 0) {
        return true;
    }
    return false;
}

bool Tile::is_top_right() const {
    if(2 != connected_tiles) {
        return false;
    }
    if(above == 0 && right == 0 && below != 0 && left != 0) {
        return true;
    }
    return false;
}

bool Tile::is_bottom_left() const {
    if(2 != connected_tiles) {
        return false;
    }
    if(above != 0 && right != 0 && below == 0 && left == 0) {
        return true;
    }
    return false;
}

bool Tile::is_bottom_right() const {
    if(2 != connected_tiles) {
        return false;
    }
    if(above != 0 && right == 0 && below == 0 && left != 0) {
        return true;
    }
    return false;
}

uint64_t Tile::get_orientation() const {
    return orientation;
}

std::ostream& operator<<(std::ostream& os, const Tile& tile) {
    os << tile.id << '\n';
    os << "Top: " << tile.top_side << '\n';
    os << "Right: " << tile.right_side << '\n';
    os << "Bottom: " << tile.bottom_side << '\n';
    os << "Left: " << tile.left_side << '\n';
    return os;
}

uint64_t Tile::get_connected_tiles() const {
    return connected_tiles;
}
