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
    std::cout << "Day5: " << binary_seat_search(input_data) << std::endl;
}

static void day6() {
    auto input_data = aoc::read_input_linewise(day6_data);
    std::cout << "Day6: " << count_customs_answers(input_data) << std::endl;
}

static void day7() {
    auto input_data = aoc::read_input_linewise(day7_data);
    std::cout << "Day7: " << unpack_bags(input_data) << std::endl;
}

static void day8() {
    auto input_data = aoc::read_input_linewise(day8_data);
    std::cout << "Day8: " << boot_sequence(input_data) << std::endl;
}

static void day9() {
    auto input_data = aoc::read_input_linewise(day9_data);
    std::cout << "Day9: " << xmas_breaker_part2(input_data, 25) << std::endl;
}

static void day10() {
    auto input_data = aoc::read_input_linewise(day10_data);
    std::cout << "Day10: " << adapter_chaining(input_data) << std::endl;
}

static void day11() {
    auto input_data = aoc::read_input_linewise(day11_data);
    std::cout << "Day10: " << musical_chairs(input_data) << std::endl;
}

int main() {
    day1();
    day2();
    day3();
    day4();
    day5();
    day6();
    day7();
    day8();
    day9();
    day10();
    day11();
    return 0;
}
