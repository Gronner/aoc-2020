#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day1Test, SampleInput) {
    std::vector<unsigned int> input_data = {1721, 979, 366, 299, 675, 1456};
    ASSERT_EQ(241861950, expense_report(input_data));
}

TEST(Day1Test, RiddleInput) {
    auto input_data = aoc::read_input_tokenwise<unsigned int>(day1_data);
    ASSERT_EQ(70276940, expense_report(input_data));
}
