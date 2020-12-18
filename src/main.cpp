#include "days.hpp"
#include "day15.hpp"

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
    std::cout << "Day11: " << musical_chairs(input_data) << std::endl;
}

static void day12() {
    auto input_data = aoc::read_input_linewise(day12_data);
    std::cout << "Day12: " << stormy_navigation(input_data) << std::endl;
}

static void day13() {
    auto input_data = aoc::read_input_linewise(day13_data);
    std::cout << "Day13: " << bus_travel_crt(input_data) << std::endl;
}

static void day14() {
    auto input_data = aoc::read_input_linewise(day14_data);
    std::cout << "Day14: " << dock_decoding(input_data) << std::endl;
}

static void day15() {
    constexpr uint64_t rounds = 2020;
    constexpr uint64_t result = memory_cards(rounds);
    std::cout << "Day15: " << result << std::endl;
}

static void day16() {
    auto input_data = aoc::read_input_linewise(day16_data);
    std::cout << "Day16: " << ticket_validation(input_data) << std::endl;
}

static void day17() {
    auto input_data = aoc::read_input_linewise(day17_data);
    std::cout << "Day17: " << conways_cubes(input_data) << std::endl;
}

static void day18() {
    auto input_data = aoc::read_input_linewise(day18_data);
    std::cout << "Day18: " << homework(input_data) << std::endl;
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
    day12();
    day13();
    day14();
    day15();
    day16();
    day17();
    day18();
    return 0;
}
