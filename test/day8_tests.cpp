#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day8Test, SampleInput1) {
    std::vector<std::string> input_data = {
        "nop +0",
        "acc +1",
        "jmp +4",
        "acc +3",
        "jmp -3",
        "acc -99",
        "acc +1",
        "jmp -4",
        "acc +6"
    };
    ASSERT_EQ(8, boot_sequence(input_data));
}

TEST(Day8Test, RiddleInput) {
    auto input_data = aoc::read_input_linewise(day8_data);
    ASSERT_EQ(969, boot_sequence(input_data));
}
