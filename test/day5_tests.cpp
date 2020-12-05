#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day5Test, SampleInput) {
    std::vector<std::string> input_data = {
        "FBFBBFFRLR",
        "BFFFBBFRRR",
        "FFFBBBFRRR",
        "BBFFBBFRLL"};
    //ASSERT_EQ(820, binary_set_search(input_data));
}

TEST(Day5Test, RiddleInput) {
    auto input_data = aoc::read_input_linewise(day5_data);
    ASSERT_EQ(524, binary_seat_search(input_data));
}
