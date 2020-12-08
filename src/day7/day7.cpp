#include "days.hpp"

#include <map>

#include "bag_type.hpp"
#include "parsing.hpp"

using BagTypeMap = std::multimap<std::string, BagType>;

static void build_map(const std::string input_line, BagTypeMap& bag_map) {
    const auto informations = aoc::grab_information(input_line,
            "(\\w+ \\w+) bags contain((:? \\d+ \\w+ \\w+ bags?,?)+| no other bags)."
            );
    const auto containing_bag = informations[1];

    const auto split_contained_bags = aoc::split_on_delimiter(informations[2], ",");
    for(const auto split_contained_bag: split_contained_bags) {
        const auto bag_information = aoc::grab_information(split_contained_bag,
                ".*(\\d+) (\\w+ \\w+).*");

        if(" no other bags" == split_contained_bag) {
            continue;
        }

        const unsigned int capacity = std::stoi(bag_information[1]);
        const std::string contained_bag = bag_information[2];

        const BagType new_bag(contained_bag, capacity);
        bag_map.insert(std::make_pair(containing_bag, new_bag));
    }
}

static unsigned int search_through_map(const std::string current_bag, const std::map<std::string, bool>& visited, const BagTypeMap bag_map) {
    unsigned int bag_count = 1;
    const auto bag_pairs= bag_map.equal_range(current_bag);
    for(auto bag_pair = bag_pairs.first; bag_pair != bag_pairs.second; ++bag_pair ) {
        bag_count += bag_pair->second.get_capacity() * search_through_map(bag_pair->second.get_bag_color(), visited, bag_map);
    }
    return bag_count;
}

unsigned int unpack_bags(const std::vector<std::string> input_data) {
    std::multimap<std::string, BagType> bag_map;
    for(const auto line: input_data) {
        build_map(line, bag_map);
    }
    std::map<std::string, bool> visited;
    return search_through_map("shiny gold", visited, bag_map) - 1;
}
