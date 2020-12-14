#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day14Test, SampleInputPart) {
    std::vector<std::string> input_data = {
        "mask = 000000000000000000000000000000X1001X",
        "mem[42] = 100",
        "mask = 00000000000000000000000000000000X0XX",
        "mem[26] = 1"
    };
    ASSERT_EQ(208, dock_decoding(input_data));
}

TEST(Day14Test, RiddleInputPart) {
    auto input_data = aoc::read_input_linewise(day14_data);
    ASSERT_EQ(3905642473893, dock_decoding(input_data));
}
