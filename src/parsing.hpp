#pragma once

#include <regex>
#include <string>
#include <vector>

namespace aoc {
std::vector<std::string> grab_information(const std::string input, const std::string expression);
bool matches(const std::string input, const std::string expression);
bool boost_matches(const std::string input, const std::string expression);
std::vector<std::string> split_on_delimiter(const std::string input, const std::string delimiter);
}

