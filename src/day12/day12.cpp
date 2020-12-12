#include "days.hpp"

#include "day12/command.hpp"
#include "day12/ship.hpp"

unsigned int stormy_navigation(std::vector<std::string> input_data) {
    Ship ferry;
    for(const auto line: input_data) {
        ferry.navigate(NavigationCommand::from_string(line));
    }
    return ferry.traveled_distance();
}

unsigned int stormy_navigation1(std::vector<std::string> input_data) {
    Ship ferry;
    for(const auto line: input_data) {
        ferry.drive(NavigationCommand::from_string(line));
    }
    return ferry.traveled_distance();
}
