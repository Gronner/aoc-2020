#include "parsing.hpp"

std::vector<std::string> aoc::grab_information(std::string input, std::string expression) {
    std::regex reg_ex(expression);
    std::smatch matcher;
    std::regex_match(input, matcher, reg_ex);
    
    std::vector<std::string> informations;
    for(auto information: matcher) {
        informations.push_back(information);
    }

    return informations;
}

