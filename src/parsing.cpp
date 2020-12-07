#include "parsing.hpp"

std::vector<std::string> aoc::grab_information(const std::string input, const std::string expression) {
    const std::regex reg_ex(expression);
    std::smatch matcher;
    std::regex_match(input, matcher, reg_ex);
    
    std::vector<std::string> informations;
    for(auto information: matcher) {
        informations.push_back(information);
    }

    return informations;
}

bool aoc::matches(const std::string input, const std::string expression) {
    const std::regex reg_ex(expression);
    std::smatch matcher;
    return std::regex_match(input, matcher, reg_ex);
}

std::vector<std::string> aoc::split_on_delimiter(const std::string input, const std::string delimiter) {
    size_t pos = 0;
    size_t last_pos = 0;
    std::string token;
    std::vector<std::string> tokens;

    while((pos = input.find(delimiter, last_pos)) != std::string::npos) {
        token = input.substr(last_pos, pos - last_pos);
        tokens.push_back(token);
        last_pos = pos + delimiter.length();
    }
    token = input.substr(last_pos, input.length() - last_pos);
    tokens.push_back(token);
    return tokens;
}
