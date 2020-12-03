#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day3Test, SampleInput) {
    std::vector<std::string> input_data = {
        "..##.......",
        "#...#...#..",
        ".#....#..#.",
        "..#.#...#.#",
        ".#...##..#.",
        "..#.##.....",
        ".#.#.#....#",
        ".#........#",
        "#.##...#...",
        "#...##....#",
        ".#..#...#.#"};
    ASSERT_EQ(336, sleeding(input_data));
}

TEST(Day3Test, RiddleInput) {
    auto input_data = aoc::read_input_linewise(day3_data);
    ASSERT_EQ(2122848000, sleeding(input_data));
}
