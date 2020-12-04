#include "parsing.hpp"

const std::vector<std::string> aoc::grab_information(const std::string input, const std::string expression) {
    const std::regex reg_ex(expression);
    std::smatch matcher;
    std::regex_match(input, matcher, reg_ex);
    
    std::vector<std::string> informations;
    for(auto information: matcher) {
        informations.push_back(information);
    }

    return informations;
}

const bool aoc::matches(const std::string input, const std::string expression) {
    const std::regex reg_ex(expression);
    std::smatch matcher;
    return std::regex_match(input, matcher, reg_ex);
}
