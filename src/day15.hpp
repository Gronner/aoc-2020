#pragma once

#include <cassert>
#include <iostream>

constexpr uint64_t memory_cards(const uint64_t rounds) {
    uint64_t numbers_turns[30000001] = {0};
    numbers_turns[14] = 1;
    numbers_turns[3] = 2;
    numbers_turns[1] = 3;
    numbers_turns[0] = 4;
    numbers_turns[9] = 5;
    auto turns = 7ULL;
    uint64_t last_number = 5;
    while(turns != (rounds + 1)) {
        uint64_t new_number;
        if(0 == numbers_turns[last_number]) {
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
