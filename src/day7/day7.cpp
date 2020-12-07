#include "days.hpp"

#include <map>

#include "bag_type.hpp"
#include "parsing.hpp"

using BagTypeMap = std::multimap<std::string, BagType>;

static void build_map(std::string input_line, BagTypeMap& bag_map) {
    auto informations = aoc::grab_information(input_line,
            "(\\w+ \\w+) bags contain((:? \\d+ \\w+ \\w+ bags?,?)+| no other bags)."
            );
    auto containing_bag = informations[1];

    auto split_contained_bags = aoc::split_on_delimiter(informations[2], ",");
    for(auto split_contained_bag: split_contained_bags) {
        auto bag_information = aoc::grab_information(split_contained_bag,
                ".*(\\d+) (\\w+ \\w+).*");

        if(" no other bags" == split_contained_bag) {
            continue;
        }

        unsigned int capacity = std::stoi(bag_information[1]);
        std::string contained_bag = bag_information[2];

        BagType new_bag(contained_bag, capacity);
        bag_map.insert(std::make_pair(containing_bag, new_bag));
    }
}

static unsigned int search_through_map(std::string current_bag, std::map<std::string, bool>& visited, BagTypeMap bag_map) {
    unsigned int bag_count = 1;
    auto range = bag_map.equal_range(current_bag);
    for(auto i = range.first; i != range.second; ++i ) {
        bag_count += i->second.get_capacity() * search_through_map(i->second.get_bag_color(), visited, bag_map);
    }
    return bag_count;
}

unsigned int unpack_bags(std::vector<std::string> input_data) {
    std::multimap<std::string, BagType> bag_map;
    for(auto line: input_data) {
        build_map(line, bag_map);
    }
    std::map<std::string, bool> visited;
    return search_through_map("shiny gold", visited, bag_map) - 1;
}
