#include "days.hpp"

#include <cassert>
#include<map>
#include "parsing.hpp"

#include <iostream>

std::string recurse_rules(std::map<uint64_t, std::string>& rules, uint64_t rule) {
    std::cout << rules[rule] << std::endl;
    if(rules[rule] == "a" || rules[rule] == "b") {
        return rules[rule];
    }
    auto tokens = aoc::split_on_delimiter(rules[rule], " ");

    std::string new_rule = "";
    new_rule.push_back('(');
    for(auto token: tokens) {
        if(token == "|") {
            new_rule.push_back('|');
        } else {
            new_rule += recurse_rules(rules, std::stoll(token));
        }
    }
    new_rule.push_back(')');
    return new_rule;
}

uint64_t solve_day19(input_t input_data) {
    /*
    input_data = { 
        "0: 4 1 5",
        "1: 2 3 | 3 2",
        "2: 4 4 | 5 5",
        "3: 4 5 | 5 4",
        "4: a",
        "5: b",
        "",
        "ababbb",
        "babab",
        "abbba",
        "aaabb",
        "aaaabb",
    };
    */
    auto mode = 0;
    std::map<uint64_t, std::string> rules;
    std::vector<std::string> data;
    for(const auto line: input_data) {
        if("" == line) {
            mode++;
            continue;
        }
        if(0 == mode) {
            auto line_content = aoc::split_on_delimiter(line, ": ");
            rules.insert(std::make_pair(std::stoll(line_content[0]), line_content[1]));
        }
        if(1 == mode) {
            data.push_back(line);
        }
    }

    std::string new_rule = recurse_rules(rules, 0);

    std::cout << new_rule << std::endl;

    uint64_t count = 0;
    for(auto datum: data) {
        if(aoc::matches(datum, new_rule)) {
            count++;
        }
    }

    return count;
}
