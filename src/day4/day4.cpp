#include "days.hpp"

#include "day4/passport.hpp"

static auto normalize_passport_layout(const std::vector<std::string> input_data) {
    std::vector<std::string> normalized_passports;
    std::string temporary_passport = "";
    for(auto line: input_data) {
        if(line.size() == 0) {
            normalized_passports.push_back(temporary_passport);
            temporary_passport.clear();
            continue;
        }
        temporary_passport += line + " ";
    }
    normalized_passports.push_back(temporary_passport); // No empty line after the last passport, add it manually
    return normalized_passports;
}

unsigned int check_valid_passports(const std::vector<std::string> input_data) {
    auto normalized_passports = normalize_passport_layout(input_data);
    unsigned int valid_count = 0;
    for(auto passport: normalized_passports) {
        auto passport_tmp = Passport::from_string(passport);
        if(passport_tmp.is_valid()) {
            valid_count++;
        }
    }
    return valid_count;
}
