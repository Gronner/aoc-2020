#include "days.hpp"

#include <iostream>

#include "aoc_input.hpp"
#include "data.hpp"

static void day1() {
    auto input_data = aoc::read_input_tokenwise<unsigned int>(day1_data);
    std::cout << "Day1: " << expense_report(input_data) << std::endl;
}

static void day2() {
    auto input_data = aoc::read_input_linewise(day2_data);
    std::cout << "Day2: " << passwort_policy_matches(input_data) << std::endl;
}

static void day3() {
    auto input_data = aoc::read_input_linewise(day3_data);
    std::cout << "Day3: " << sleeding(input_data) << std::endl;
}

static void day4() {
    auto input_data = aoc::read_input_linewise(day4_data);
    std::cout << "Day4: " << check_valid_passports(input_data) << std::endl;
}

static void day5() {
    auto input_data = aoc::read_input_linewise(day5_data);
    std::cout << "Day5: " << binary_set_search(input_data) << std::endl;
}

int main() {
    day1();
    day2();
    day3();
    day4();
    day5();
    return 0;
}
