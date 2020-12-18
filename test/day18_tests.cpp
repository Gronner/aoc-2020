#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day18Test, SampleInputPart1) {
    std::vector<std::string> input_data = {
        "1 + 2 * 3 + 4 * 5 + 6",
    };
    ASSERT_EQ(231, homework(input_data));
}

TEST(Day18Test, SampleInputPart2) {
    std::vector<std::string> input_data = {
        "1 + (2 * 3) + (4 * (5 + 6))",
    };
    ASSERT_EQ(51, homework(input_data));
}

TEST(Day18Test, SampleInputPart3) {
    std::vector<std::string> input_data = {
        "2 * 3 + (4 * 5)",
    };
    ASSERT_EQ(46, homework(input_data));
}

TEST(Day18Test, SampleInputPart4) {
    std::vector<std::string> input_data = {
        "5 + (8 * 3 + 9 + 3 * 4 * 3)",
    };
    ASSERT_EQ(1445, homework(input_data));
}

TEST(Day18Test, SampleInputPart5) {
    std::vector<std::string> input_data = {
        "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))",
    };
    ASSERT_EQ(669060, homework(input_data));
}

TEST(Day18Test, SampleInputPart6) {
    std::vector<std::string> input_data = {
        "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2",
    };
    ASSERT_EQ(23340, homework(input_data));
}

TEST(Day18Test, RiddleInputPart) {
    auto input_data = aoc::read_input_linewise(day18_data);
    ASSERT_EQ(70722650566361, homework(input_data));
}
