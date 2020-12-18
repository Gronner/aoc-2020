#include "gtest/gtest.h"

#include "day15.hpp"

TEST(Day15Test, RiddleInputPart) {
    constexpr auto result = memory_cards(2020);
    ASSERT_EQ(614, result);
}

TEST(Day15Test, DISABLED_RiddleInputPart2) {
    ASSERT_EQ(1065, memory_cards(30000000));
}
