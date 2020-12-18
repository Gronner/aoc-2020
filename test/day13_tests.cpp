#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day13Test, SampleInput1) {
    std::vector<std::string> input_data = {
        "",
        "17,x,13,19",
    };
    ASSERT_EQ(3417, bus_travel_crt(input_data));
}

TEST(Day13Test, SampleInput2) {
    std::vector<std::string> input_data = {
        "",
        "67,7,59,61",
    };
    ASSERT_EQ(754018, bus_travel_crt(input_data));
}

TEST(Day13Test, SampleInput3) {
    std::vector<std::string> input_data = {
        "",
        "67,x,7,59,61",
    };
    ASSERT_EQ(779210, bus_travel_crt(input_data));
}

TEST(Day13Test, SampleInput4) {
    std::vector<std::string> input_data = {
        "",
        "67,7,x,59,61",
    };
    ASSERT_EQ(1261476, bus_travel_crt(input_data));
}

TEST(Day13Test, SampleInput5) {
    std::vector<std::string> input_data = {
        "",
        "1789,37,47,1889",
    };
    ASSERT_EQ(1202161486, bus_travel_crt(input_data));
}

TEST(Day13Test, RiddleInput) {
    auto input_data = aoc::read_input_linewise(day13_data);
    ASSERT_EQ(247086664214628, bus_travel_crt(input_data));
}
