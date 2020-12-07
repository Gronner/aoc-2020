#include "bag_type.hpp"

BagType::BagType(std::string bag_color, unsigned int capacity) : 
    bag_color(bag_color), capacity(capacity) {}

std::string BagType::get_bag_color() {
    return bag_color;
}

unsigned int BagType::get_capacity() {
    return capacity;
}
