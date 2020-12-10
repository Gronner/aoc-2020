#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day10Test, SampleInput1) {
    std::vector<std::string> input_data = {
        "16",
        "10",
        "15",
        "5",
        "1",
        "11",
        "7",
        "19",
        "6",
        "12",
        "4"
    };
    ASSERT_EQ(8, adapter_chaining(input_data));
}

TEST(Day10Test, SampleInput2) {
    std::vector<std::string> input_data = {
        "28",
        "33",
        "18",
        "42",
        "31",
        "14",
        "46",
        "20",
        "48",
        "47",
        "24",
        "23",
        "49",
        "45",
        "19",
        "38",
        "39",
        "11",
        "1",
        "32",
        "25",
        "35",
        "8",
        "17",
        "7",
        "9",
        "4",
        "2",
        "34",
        "10",
        "3"
    };
    ASSERT_EQ(19208, adapter_chaining(input_data));
}

TEST(Day10Test, RiddleInput) {
    auto input_data = aoc::read_input_linewise(day10_data);
    ASSERT_EQ(442136281481216, adapter_chaining(input_data));
}
