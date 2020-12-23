#include "days.hpp"

#include <algorithm>
#include <execution>
#include <string>
#include <iostream>
#include <map>

constexpr uint64_t MAX_ROUNDS = 100;

using cups_t = std::map<uint64_t, uint64_t>;

// static void print_cups(const cups_t cups);
static std::vector<uint64_t> taken = {0, 0, 0};

static void pick_cups(cups_t& cups, const uint64_t current_cup) {
    taken[0] = cups[current_cup];
    taken[1] = cups[taken[0]];
    taken[2] = cups[taken[1]];
    cups[current_cup] = cups[taken[2]];
}

auto get_current_label(const cups_t cups) {
    return *cups.begin();
}

auto find_next_cup(const cups_t cups, uint64_t current_cup) {
    const auto smallest_cup = (*cups.begin()).first;
    const auto biggest_cup = (*cups.rbegin()).first;

    uint64_t next_cup_label = current_cup - 1;
    if((smallest_cup - 1) == next_cup_label) {
        next_cup_label = biggest_cup;
    }
    while(taken.end() != std::find(taken.begin(), taken.end(), next_cup_label)) {
        next_cup_label--;
        if(0 == next_cup_label) {
            next_cup_label = biggest_cup;
        }
    }
    return next_cup_label;
}

static void print_cups(cups_t cups, const uint64_t current_cup=1) {
    auto output_cup = cups[current_cup];
    std::cout << current_cup;
    while(current_cup != output_cup) {
        std::cout << output_cup;
        output_cup = cups[output_cup];
    }
    std::cout << std::endl;
}

static void insert_taken(cups_t& cups, const uint64_t current_cup) {
    cups[taken[2]] = cups[current_cup];
    cups[current_cup] = taken[0];
}

uint64_t solve_day23() {
    cups_t cups;
    cups.insert(std::make_pair(7, 1));
    cups.insert(std::make_pair(1, 6));
    cups.insert(std::make_pair(6, 8));
    cups.insert(std::make_pair(8, 9));
    cups.insert(std::make_pair(9, 2));
    cups.insert(std::make_pair(2, 5));
    cups.insert(std::make_pair(5, 4));
    cups.insert(std::make_pair(4, 3));
    cups.insert(std::make_pair(3, 7));
    /*
    cups.insert(std::make_pair(3, 8));
    cups.insert(std::make_pair(8, 9));
    cups.insert(std::make_pair(9, 1));
    cups.insert(std::make_pair(1, 2));
    cups.insert(std::make_pair(2, 5));
    cups.insert(std::make_pair(5, 4));
    cups.insert(std::make_pair(4, 6));
    cups.insert(std::make_pair(6, 7));
    cups.insert(std::make_pair(7, 3));
    */
    /*
    auto current_insertion = 10;
    for(uint64_t i = 11; i < 1'000'001; ++i) {
        cups.insert(std::make_pair(current_insertion, i));
        current_insertion = i;
    }
    cups.insert(std::make_pair(current_insertion, 7));
    */

    auto current_cup = 7;
    for(uint64_t round = 0; round < MAX_ROUNDS; ++round) {
        if(0 == round % 100) {
            std::cout << round << std::endl;
        }
        pick_cups(cups, current_cup);
        const auto destination = find_next_cup(cups, current_cup);
        insert_taken(cups, destination);
        current_cup = cups[current_cup];
    }

    print_cups(cups);

    const auto first_after_1 = cups[1];
    const auto second_after_1= cups[first_after_1];
    return first_after_1 * second_after_1;
}
