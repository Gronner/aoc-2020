#pragma once

#include <cstdint>
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
        uint64_t flipped;
        uint64_t connected_tiles;
        void rotate_picture();
        void flip_picture();
    public:
        Tile(const std::vector<std::string> tile);
        void rotate();
        void flip();
        uint64_t fit(const Tile other);
        bool is_fit_right(const Tile other) const;
        bool is_fit_below(const Tile other) const;
        void piece_together(Tile other, uint64_t spot);
        uint64_t get_id() const;
        uint64_t get_orientation() const;
        uint64_t get_flipped() const;
        std::vector<std::string> get_picture() const;
        bool is_corner_piece() const;
        bool already_linked(const Tile other) const;
        bool is_top_left() const;
        bool is_top_right() const;
        bool is_bottom_left() const;
        bool is_bottom_right() const;
        bool has_tile_below() const;
        bool has_right_tile() const;
        void strip_sides();
        uint64_t get_tile_below() const;
        uint64_t get_right_tile() const;
};
