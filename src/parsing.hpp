#pragma once

#include <regex>
#include <string>
#include <vector>

namespace aoc {
const std::vector<std::string> grab_information(const std::string input, const std::string expression);
const bool matches(const std::string input, const std::string expression);
}

