#include "days.hpp"

#include <algorithm>
#include <execution>
#include <string>
#include <unordered_map>

using cups_t = std::unordered_map<uint64_t, uint64_t>;

uint64_t solve_day23() {
    constexpr uint64_t MAX_ROUNDS = 10'000'000;
    std::vector<uint64_t> taken = {0, 0, 0};

    cups_t cups;
    cups.insert(std::make_pair(7, 1));
    cups.insert(std::make_pair(1, 6));
    cups.insert(std::make_pair(6, 8));
    cups.insert(std::make_pair(8, 9));
    cups.insert(std::make_pair(9, 2));
    cups.insert(std::make_pair(2, 5));
    cups.insert(std::make_pair(5, 4));
    cups.insert(std::make_pair(4, 3));
    cups.insert(std::make_pair(3, 10));
    auto current_insertion = 10;
    for(uint64_t i = 11; i < 1'000'001; ++i) {
        cups.insert(std::make_pair(current_insertion, i));
        current_insertion = i;
    }
    cups.insert(std::make_pair(current_insertion, 7));

    auto current_cup = 7;
    for(uint64_t round = 0; round < MAX_ROUNDS; ++round) {
        // Take out
        taken[0] = cups[current_cup];
        taken[1] = cups[taken[0]];
        taken[2] = cups[taken[1]];
        cups[current_cup] = cups[taken[2]];

        // Get destination
        const auto smallest_cup = 1ULL;
        const auto biggest_cup = 1'000'000ULL;

        uint64_t next_cup_label = current_cup - 1;
        if((smallest_cup - 1) == next_cup_label) {
            next_cup_label = biggest_cup;
        }
        while(taken.end() != std::find(taken.cbegin(), taken.cend(), next_cup_label)) {
            next_cup_label--;
            if(0 == next_cup_label) {
                next_cup_label = biggest_cup;
            }
        }
        const auto destination = next_cup_label;

        // Insert taken
        cups[taken[2]] = cups[destination];
        cups[destination] = taken[0];

        current_cup = cups[current_cup];
    }
    const auto first_after_1 = cups[1];
    const auto second_after_1= cups[first_after_1];
    return first_after_1 * second_after_1;
}
