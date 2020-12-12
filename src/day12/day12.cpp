#include "days.hpp"

#include "day12/ship.hpp"

unsigned int stormy_navigation(std::vector<std::string> input_data) {
    Ship ferry;
    for(const auto line: input_data) {
        ferry.navigate(line);
    }
    return ferry.traveled_distance();
}