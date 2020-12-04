#include "gtest/gtest.h"

#include "aoc_input.hpp"
#include "data.hpp"
#include "days.hpp"

TEST(Day4Test, SampleInput) {
    std::vector<std::string> input_data = {
        "ecl:gry pid:860033327 eyr:2020 hcl:#fffffd",
        "byr:1937 iyr:2017 cid:147 hgt:183cm",
        "",
        "iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884",
        "hcl:#cfa07d byr:1929",
        "",
        "hcl:#ae17e1 iyr:2013",
        "eyr:2024",
        "ecl:brn pid:760753108 byr:1931",
        "hgt:179cm",
        "",
        "hcl:#cfa07d eyr:2025 pid:166559648",
        "iyr:2011 ecl:brn hgt:59in"};
    ASSERT_EQ(2, check_valid_passports(input_data));
}

TEST(Day4Test, RiddleInput) {
    auto input_data = aoc::read_input_linewise(day4_data);
    ASSERT_EQ(210, check_valid_passports(input_data));
}
