#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day12Test, SampleInputPart1) {
    std::vector<std::string> input_data = {
        "F10",
        "N3",
        "F7",
        "R90",
        "F11"
    };
    ASSERT_EQ(25, stormy_navigation1(input_data));
}

TEST(Day12Test, RiddleInputPart1) {
    auto input_data = aoc::read_input_linewise(day12_data);
    ASSERT_EQ(1838, stormy_navigation1(input_data));
}

TEST(Day12Test, SampleInputPart2) {
    std::vector<std::string> input_data = {
        "F10",
        "N3",
        "F7",
        "R90",
        "F11"
    };
    ASSERT_EQ(286, stormy_navigation(input_data));
}

TEST(Day12Test, RiddleInputPart2) {
    auto input_data = aoc::read_input_linewise(day12_data);
    ASSERT_EQ(89936, stormy_navigation(input_data));
}
