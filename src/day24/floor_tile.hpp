#pragma once

#include <map>
#include <string>
#include <vector>

class FloorTile {
    private:
        bool color;
        std::vector<int64_t> coordinates;
    public:
        FloorTile(std::vector<int64_t> coordinates);
        void flip();
        bool get_color() const;
        std::vector<int64_t> get_neigbour(const std::string direction) const;
        std::vector<int64_t> get_coordinates() const;
};
