#pragma once

#include <string>

class BagType {
private:
    const std::string bag_color;
    const unsigned int capacity;
public:
    BagType(std::string bag_color, unsigned int capacity);
    std::string get_bag_color() const;
    unsigned int get_capacity() const;
};
