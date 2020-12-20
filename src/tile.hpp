#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Tile {
    private:
        uint64_t id;
        std::vector<std::string> tile_picture;
        std::string top_side;
        std::string right_side;
        std::string bottom_side;
        std::string left_side;
        uint64_t above;
        uint64_t right;
        uint64_t below;
        uint64_t left;
        uint64_t orientation;
        bool flipped;
        uint64_t connected_tiles;
    public:
        Tile(std::vector<std::string> tile);
        void rotate();
        void flip();
        bool orient_edges(Tile& other);
        uint64_t get_id() const;
        uint64_t get_orientation() const;
        uint64_t get_connected_tiles() const;
        bool is_corner_piece() const;
        bool already_linked(const Tile other) const;
        void clear_state();
        bool is_top_left() const;
        bool is_top_right() const;
        bool is_bottom_left() const;
        bool is_bottom_right() const;
        friend std::ostream& operator<<(std::ostream& os, const Tile& tile);
};
