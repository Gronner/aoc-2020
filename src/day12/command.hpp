#pragma once

#include <string>

#include "parsing.hpp"

struct NavigationCommand {
    static NavigationCommand from_string(const std::string command) {
        const auto command_parsed = aoc::grab_information(command,
                                                          "(\\w)(\\d*)");
        return NavigationCommand(command_parsed[1].at(0),
                                 std::stoi(command_parsed[2]));
    };
    char argument;
    int value;
};
