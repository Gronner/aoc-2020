#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day2Test, SampleInput) {
    std::vector<std::string> input_data = {"1-3 a: abcde", "1-3 b: cdefg", "2-9 c: ccccccccc"};
    ASSERT_EQ(1, passwort_policy_matches(input_data));
}

TEST(Day2Test, RiddleInput) {
    auto input_data = aoc::read_input_linewise(day2_data);
    ASSERT_EQ(485, passwort_policy_matches(input_data));
}
