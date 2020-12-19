#include "days.hpp"

#include<map>
#include "parsing.hpp"

static std::map<int, std::string> cached_rules;
std::string recurse_rules(const std::map<uint64_t, std::string> rules, const uint64_t rule_idx) {
    const auto rule = (*rules.find(rule_idx)).second;
    if(rule == "\"a\"" || rule == "\"b\"") {
        return rule == "\"a\"" ? "a" : "b";
    }
    if(cached_rules.contains(rule_idx)) {
        return cached_rules[rule_idx];
    }
    const auto tokens = aoc::split_on_delimiter(rule, " ");

    std::string new_rule = "";
    new_rule += ("(?:");
    if(8 == rule_idx) {
        new_rule += recurse_rules(rules, 42);
        // new_rule.push_back('+'); Part 2
    } else if(11 == rule_idx) {
        const auto expr42 = recurse_rules(rules, 42);
        const auto expr31 = recurse_rules(rules, 31);
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
        for(const auto token: tokens) {
            if(token == "|") {
                new_rule.push_back('|');
            } else {
                new_rule += recurse_rules(rules, std::stoll(token));
            }
        }
    }
    new_rule.push_back(')');
    cached_rules.insert(std::make_pair(rule_idx, new_rule));
    return new_rule;
}

uint64_t monster_messages(const input_t input_data) {
    cached_rules.clear();
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
    rules[8] = "42 | 42 8"; // This basically means 42+ in regex
    rules[11] = "42 31 | 42 11 31"; // This basically means 42{1}31{1} | 42{2}31{2} | ... | 42{i}31{i} in regex and with eyeballing one can see that recursion depth is not unlimited and resonable. Sadly something breaks here in std::regex or I have an error elsewhere

    const std::string new_rule = recurse_rules(rules, 0);

    uint64_t count = 0;
    for(const auto datum: data) {
        if(aoc::matches(datum, new_rule)) {
            count++;
        }
    }

    return count;
}
