#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day6Test, SampleInput) {
    std::vector<std::string> input_data = {
        "abc",
        "",
        "a",
        "b",
        "c",
        "",
        "ab",
        "ac",
        "",
        "a",
        "a",
        "a",
        "a",
        "",
        "b"};
    ASSERT_EQ(6, count_customs_answers(input_data));
}

TEST(Day6Test, RiddleInput) {
    auto input_data = aoc::read_input_linewise(day6_data);
    ASSERT_EQ(3466, count_customs_answers(input_data));
}
