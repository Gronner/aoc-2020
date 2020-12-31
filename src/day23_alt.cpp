#include "days.hpp"

#include <algorithm>
#include <string>

uint64_t solve_day23() {
    constexpr uint64_t MAX_ROUNDS = 10'000'000;
    std::vector<uint64_t> taken = {0, 0, 0};

    uint64_t cups[1'000'000]; // = {0, 6, 5, 10, 3, 4, 8, 1, 9, 2};
    cups[0] = 0;
    cups[1] = 6;
    cups[2] = 5;
    cups[3] = 10;
    cups[4] = 3;
    cups[5] = 4;
    cups[6] = 8;
    cups[7] = 1;
    cups[8] = 9;
    cups[9] = 2;
    auto current_insertion = 10ULL;
    for(uint64_t i = 11; i < 1'000'001; ++i) {
        cups[current_insertion] = i;
        current_insertion = i;
    }
    cups[current_insertion] = 7ULL;

    auto current_cup = 7;
    for(uint64_t round = 0; round < MAX_ROUNDS; ++round) {
        // Take out
        taken[0] = cups[current_cup];
        taken[1] = cups[taken[0]];
        taken[2] = cups[taken[1]];
        cups[current_cup] = cups[taken[2]];

        // Get destination
        const auto smallest_cup = 1;
        const auto biggest_cup = 1'000'000;

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
