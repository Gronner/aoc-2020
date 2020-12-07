#pragma once

#include <string>

class BagType {
private:
    std::string bag_color;
    unsigned int capacity;
public:
    BagType(std::string bag_color, unsigned int capacity);
    std::string get_bag_color();
    unsigned int get_capacity();
};
