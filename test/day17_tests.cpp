#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day17Test, SampleInputPart) {
    std::vector<std::string> input_data = {
        ".#.",
        "..#",
        "###",
    };
    ASSERT_EQ(848, conways_cubes(input_data));
}

TEST(Day17Test, RiddleInputPart) {
    auto input_data = aoc::read_input_linewise(day17_data);
    ASSERT_EQ(1696, conways_cubes(input_data));
}
