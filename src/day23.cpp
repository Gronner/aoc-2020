#include "days.hpp"

#include <algorithm>
#include <execution>
#include <string>
#include <iostream>
#include <list>

constexpr uint64_t MAX_ROUNDS = 100;//10'000'000;

using cups_t = std::vector<uint64_t>;

// static void print_cups(const cups_t cups);

static auto pick_cups(cups_t& cups) {
    auto taken = cups_t(std::next(cups.begin(), 1), std::next(cups.begin(), 4));
    cups.erase(std::next(cups.begin(), 1), std::next(cups.begin(), 4));
    return taken;
}

auto get_current_label(const cups_t cups) {
    return *cups.begin();
}

auto find_next_cup(const cups_t cups, const cups_t taken) {
    const auto [smallest_cup, biggest_cup] = std::minmax_element(cups.begin(), cups.end());
    const uint64_t current_cup_label = *cups.begin();
    uint64_t next_cup_label = current_cup_label - 1;
    if((*smallest_cup - 1) == next_cup_label) {
        next_cup_label = *biggest_cup;
    }
    while(taken.end() != std::find(taken.begin(), taken.end(), next_cup_label)) {
        next_cup_label--;
        if(0 == next_cup_label) {
            next_cup_label = *biggest_cup;
        }
    }
    auto found_cup = std::find(std::execution::par, cups.cbegin(), cups.cend(), next_cup_label);
    if(cups.end() != found_cup) {
        return std::distance(cups.begin(), found_cup);
    }
    return 0L;
}

static void print_cups(const cups_t cups) {
    for(auto cup: cups) {
        std::cout << cup;
    }
    std::cout << std::endl;
}

uint64_t solve_day23() {
    cups_t cups = {
        7, 1, 6, 8, 9, 2, 5, 4, 3,
        // 3, 8, 9, 1, 2, 5, 4, 6, 7,
    };
    /*
    for(uint64_t i = 8; i < 1'000'001; ++i) {
        cups.push_back(i);
    }
    */
    for(uint64_t round = 0; round < MAX_ROUNDS; ++round) {
        if(0 == round % 10'000) {
            std::cout << round << std::endl;
        }
        auto taken = pick_cups(cups);
        auto next_cup = find_next_cup(cups, taken);
        cups.insert(std::next(cups.begin(), next_cup + 1), taken.begin(), taken.end());
        std::rotate(cups.begin(), std::next(cups.begin(), 1), cups.end());
    }

    // auto cup_labeled_1 = std::find(std::execution::par_unseq, cups.begin(), cups.end(), 1);
    while(1 != *cups.begin()) {
        std::rotate(cups.begin(), std::next(cups.begin(), 1), cups.end());
    }

    print_cups(cups);
    return 0;
    // return *std::next(cup_labeled_1, 1) * *std::next(cup_labeled_1, 2);
}
