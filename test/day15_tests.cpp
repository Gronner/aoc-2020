#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day15Test, RiddleInputPart1) {
    auto input_data = aoc::read_input_linewise(day15_data);
    ASSERT_EQ(614, memory_cards(input_data, 2020));
}

TEST(Day15Test, RiddleInputPart2) {
    auto input_data = aoc::read_input_linewise(day15_data);
    ASSERT_EQ(1065, memory_cards(input_data, 30000000));
}
