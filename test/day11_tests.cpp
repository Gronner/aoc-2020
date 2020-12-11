#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day11Test, SampleInput) {
    std::vector<std::string> input_data = {
        "L.LL.LL.LL",
        "LLLLLLL.LL",
        "L.L.L..L..",
        "LLLL.LL.LL",
        "L.LL.LL.LL",
        "L.LLLLL.LL",
        "..L.L.....",
        "LLLLLLLLLL",
        "L.LLLLLL.L",
        "L.LLLLL.LL"
    };
    ASSERT_EQ(26, musical_chairs(input_data));
}

TEST(Day11Test, RiddleInput) {
    auto input_data = aoc::read_input_linewise(day11_data);
    ASSERT_EQ(2159, musical_chairs(input_data));
}
