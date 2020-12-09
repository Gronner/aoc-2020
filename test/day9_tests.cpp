#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day9Test, SampleInput) {
    std::vector<std::string> input_data = {
        "35",
        "20", 
        "15",
        "25",
        "47",
        "40",
        "62",
        "55",
        "65",
        "95",
        "102",
        "117",
        "150",
        "182",
        "127",
        "219",
        "299",
        "277",
        "309",
        "576"
    };
    ASSERT_EQ(62, xmas_breaker_part2(input_data, 5));
}

TEST(Day9Test, RiddleInput) {
    auto input_data = aoc::read_input_linewise(day9_data);
    ASSERT_EQ(1766397, xmas_breaker_part2(input_data, 25));
}
