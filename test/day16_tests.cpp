#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day16Test, RiddleInputPart) {
    auto input_data = aoc::read_input_linewise(day16_data);
    ASSERT_EQ(1001849322119, ticket_validation(input_data));
}
