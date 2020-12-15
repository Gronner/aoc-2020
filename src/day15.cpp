#include "days.hpp"

#include <map>

#include <iostream>
#include "parsing.hpp"

uint64_t memory_cards(std::vector<std::string> input) {
    std::vector<std::string> starting_numbers = aoc::split_on_delimiter(input[0], ",");
    std::map<uint64_t, uint64_t> numbers_turns;
    numbers_turns.insert(std::make_pair(14, 1));
    numbers_turns.insert(std::make_pair(3, 2));
    numbers_turns.insert(std::make_pair(1, 3));
    numbers_turns.insert(std::make_pair(0, 4));
    numbers_turns.insert(std::make_pair(9, 5));
    uint64_t turns = numbers_turns.size() + 2;
    uint64_t last_number = 5;
    while(turns != 30000001) {
        uint64_t new_number;
        if(0 == numbers_turns.count(last_number)) {
            new_number = 0;
        } else {
            new_number = turns - numbers_turns[last_number] - 1;
        }
        numbers_turns[last_number] = turns - 1;
        last_number = new_number;
        turns++;
    }
    return last_number;
}
