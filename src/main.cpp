#include "days.hpp"

#include <iostream>

#include "aoc_input.hpp"
#include "data.hpp"

static void day1() {
    auto input_data = aoc::read_input_tokenwise<unsigned int>(day1_data);
    std::cout << expense_report(input_data) << std::endl;
}

int main() {
    day1();
    //day2();
    //day3();
    return 0;
}
