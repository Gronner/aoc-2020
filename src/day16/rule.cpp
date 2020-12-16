#include "day16/rule.hpp"

#include "parsing.hpp"

Rule::Rule(std::string name, uint64_t min_1, uint64_t max_1, uint64_t min_2, uint64_t max_2) :
    name(name), min_1(min_1), max_1(max_1), min_2(min_2), max_2(max_2) {}

Rule Rule::from_string(std::string input) {
    auto ticket_rule = aoc::grab_information(input, "([ \\w]*): (\\d*)-(\\d*) or (\\d*)-(\\d*)");
    return Rule(ticket_rule[1],
            std::stoi(ticket_rule[2]),
            std::stoi(ticket_rule[3]),
            std::stoi(ticket_rule[4]),
            std::stoi(ticket_rule[5]));
}

bool Rule::is_fullfilled(uint64_t value) {
    return ((min_1 <= value) && (value <= max_1)) || ((min_2 <= value) && (value <= max_2));
}

std::string Rule::get_name() const {
    return name;
}
