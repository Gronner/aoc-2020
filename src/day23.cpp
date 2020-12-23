#include "days.hpp"

#include <algorithm>
#include <execution>
#include <string>
#include <iostream>

// static void print_cups(const std::vector<uint64_t> cups);

static auto pick_cups(std::vector<uint64_t>& cups) {
    auto taken = std::vector<uint64_t>(cups.begin() + 1, cups.begin() + 4);
    cups.erase(cups.begin() + 1, cups.begin() + 4);
    return taken;
}

auto get_current_label(const std::vector<uint64_t> cups) {
    return cups[0];
}

auto find_next_cup(const std::vector<uint64_t> cups) {
    const auto [smallest_cup, biggest_cup] = std::minmax_element(std::execution::par_unseq, cups.begin(), cups.end());
    uint64_t current_cup_label = cups[0];
    uint64_t next_cup_label = current_cup_label - 1;
    while(1) {
        if(next_cup_label < *smallest_cup) {
            next_cup_label = *biggest_cup;
        }
        auto found_cup = std::find(std::execution::par_unseq, cups.cbegin(), cups.cend(), next_cup_label);
        if(cups.end() != found_cup) {
            return std::distance(cups.begin(), found_cup);
        }
        next_cup_label--;
    }
    return 0L;
}

/*
static void print_cups(const std::vector<uint64_t> cups) {
    for(auto cup: cups) {
        std::cout << cup;
    }
    std::cout << std::endl;
}
*/

uint64_t solve_day23() {
    std::vector<uint64_t> cups = {
        7, 1, 6, 8, 9, 2, 5, 4, 3,
        // 3, 8, 9, 1, 2, 5, 4, 6, 7,
    };
    for(uint64_t i = 8; i < 1'000'001; ++i) {
        cups.push_back(i);
    }
    for(auto round = 0; round < 10'000'000; ++round) {
        auto taken = pick_cups(cups);
        auto next_cup = find_next_cup(cups);
        cups.insert(cups.begin() + next_cup + 1, taken.begin(), taken.end());
        std::rotate(cups.begin(), cups.begin() + 1, cups.end());
    }

    auto cup_labeled_1 = std::find(std::execution::par_unseq, cups.begin(), cups.end(), 1);
    return *(cup_labeled_1 + 1) * *(cup_labeled_1 + 2);
}
