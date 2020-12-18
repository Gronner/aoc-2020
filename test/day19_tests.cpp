#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day19Test, SampleInputPart) {
    std::vector<std::string> input_data = {
    };
    ASSERT_EQ(0, solve_day19(input_data));
}

TEST(Day19Test, RiddleInputPart) {
    auto input_data = aoc::read_input_linewise(day18_data);
    ASSERT_EQ(0, solve_day19(input_data));
}
