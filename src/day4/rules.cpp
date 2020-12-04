#include "day4/rules.hpp"

#include <set>

#include "parsing.hpp"

static bool year_is_valid(std::string year, unsigned int min_year, unsigned int max_year) {
    auto year_information = aoc::grab_information(year, "(\\d{4})");
    if(year_information[0].size() == 0) {
        return false;
    }
    unsigned int year_value = std::stoul(year_information[1]);
    return min_year <= year_value && year_value <= max_year;
}

bool birth_year_is_valid(std::string birth_year) { 
    return year_is_valid(birth_year, 1920, 2002);
}

bool issue_year_is_valid(std::string issue_year) {
    return year_is_valid(issue_year, 2010, 2020);
}

bool expiration_year_is_valid(std::string expiration_year) {
    return year_is_valid(expiration_year, 2020, 2030);
}

bool height_is_valid(std::string height) {
    auto height_split = aoc::grab_information(height, "(\\d{1,3})(in|cm)");
    if(height_split[0].size() == 0) {
        return false;
    }
    unsigned int height_value = std::stoul(height_split[1]);
    if(height_split[2] == "cm") {
        return 150 <= height_value && height_value <= 193;
    } else {
        return 59 <= height_value && height_value <= 76;
    }
}

bool hair_color_is_valid(std::string hair_color) {
    return aoc::matches(hair_color, "#[0-9a-f]{6}");
}

bool eye_color_is_valid(std::string eye_color) {
    const std::set<std::string> eye_colors = {
        "amb", "blu", "brn", "gry", "grn", "hzl", "oth"
    };
    return eye_colors.find(eye_color) != eye_colors.end();
}

bool passport_id_is_valid(std::string passport_id) {
    return aoc::matches(passport_id, "\\d{9}");
}
