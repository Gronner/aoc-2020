#include "days.hpp"

#include<map>
#include "parsing.hpp"

std::string recurse_rules(std::map<uint64_t, std::string>& rules, uint64_t rule) {
    if(rules[rule] == "\"a\"" || rules[rule] == "\"b\"") {
        return rules[rule] == "\"a\"" ? "a" : "b";
    }
    auto tokens = aoc::split_on_delimiter(rules[rule], " ");

    std::string new_rule = "";
    new_rule += ("(?:");
    if(8 == rule) {
        new_rule += recurse_rules(rules, 42);
        // new_rule.push_back('+'); Part 2
    } else if(11 == rule) {
        auto expr42 = recurse_rules(rules, 42);
        auto expr31 = recurse_rules(rules, 31);
        constexpr auto stop_recursion_at = 1;  // Higher for Part 2 in theory
        for(auto i = 1; i < (stop_recursion_at + 1); i++) {
            new_rule.push_back('(');
            new_rule += expr42;
            new_rule += "{" + std::to_string(i) + "}";
            new_rule += expr31;
            new_rule += "{" + std::to_string(i) + "}";
            new_rule.push_back(')');
            new_rule.push_back('|');
        }
    } else {
        for(auto token: tokens) {
            if(token == "|") {
                new_rule.push_back('|');
            } else {
                new_rule += recurse_rules(rules, std::stoll(token));
            }
        }
    }
    new_rule.push_back(')');
    return new_rule;
}

uint64_t monster_messages(input_t input_data) {
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
    rules[8] = "42 | 42 8";
    rules[11] = "42 31 | 42 11 31";

    std::string new_rule = recurse_rules(rules, 0);

    uint64_t count = 0;
    for(auto datum: data) {
        if(aoc::matches(datum, new_rule)) {
            count++;
        }
    }

    return count;
}
