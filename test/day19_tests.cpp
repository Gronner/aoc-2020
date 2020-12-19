#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day19Test, SampleInputPart) {
    std::vector<std::string> input_data = {
        "0: 4 1 5",
        "1: 2 3 | 3 2",
        "2: 4 4 | 5 5",
        "3: 4 5 | 5 4",
        "4: \"a\"",
        "5: \"b\"",
        "",
        "ababbb",
        "bababa",
        "abbbab",
        "aaabbb",
        "aaaabbb",
    };
    ASSERT_EQ(2, monster_messages(input_data));
}

TEST(Day19Test, RiddleInputPart) {
    auto input_data = aoc::read_input_linewise(day19_data);
    ASSERT_EQ(192, monster_messages(input_data));
}
