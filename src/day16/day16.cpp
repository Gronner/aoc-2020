#include "days.hpp"

#include <map>
#include <set>

#include "day16/rule.hpp"
#include "parsing.hpp"

uint64_t ticket_validation(input_t input_data) {
    auto mode = 0;
    std::vector<Rule> rules;
    std::vector<std::vector<uint64_t>> tickets;
    std::vector<uint64_t> my_ticket;
    for(auto line: input_data) {
        if("" == line) {
            mode++;
            continue;
        }
        if(0 == mode) {
            rules.push_back(Rule::from_string(line));
            continue;
        }
        if(1 == mode) {
            if("your ticket:" == line) {
                continue;
            }
            auto ticket_description = aoc::split_on_delimiter(line, ",");
            for(auto value: ticket_description) {
                my_ticket.push_back(std::stoi(value));
            }
            continue;
        }
        if("nearby tickets:" == line) {
            continue;
        }
        auto ticket_description= aoc::split_on_delimiter(line, ",");
        std::vector<uint64_t> ticket_values;
        for(auto value: ticket_description) {
            ticket_values.push_back(std::stoi(value));
        }
        tickets.push_back(ticket_values);
    }

    auto tickets_tmp = tickets;
    for(auto ticket: tickets) {
        for(auto value: ticket) {
            auto valid = false;
            for(auto rule: rules) {
                if(rule.is_fullfilled(value)){
                    valid = true;
                    break;
                }
            }
            if(!valid) {
                auto found_ticket = std::find(tickets_tmp.begin(), tickets_tmp.end(), ticket);
                if(found_ticket != tickets_tmp.end()) {
                    tickets_tmp.erase(found_ticket);
                }
            }
        }
    }
    auto valid_tickets = tickets_tmp;

    std::vector<std::set<std::string>> possible_values_names;
    for(auto i = 0U; i < valid_tickets[0].size(); ++i) {
        std::set<std::string> possible_names;
        for(auto rule: rules) {
            possible_names.insert(rule.get_name());
        }
        possible_values_names.push_back(possible_names);
    }

    for(auto ticket: valid_tickets) {
        auto field_idx = 0U;
        for(auto value: ticket) {
            for(auto rule = rules.begin(); rule != rules.end(); ++rule) {
                if(!rule->is_fullfilled(value)) {
                    possible_values_names[field_idx].erase(rule->get_name());
                }
            }
            field_idx++;
        }
    }

    auto satisfied = false;
    auto enumerate = 0U;
    while(!satisfied) {
        std::string to_eliminate = "";
        auto possible_names = possible_values_names[enumerate];
        if(1 == possible_names.size()) {
            to_eliminate = *(possible_names.begin());
            for(auto& possible_names_tmp: possible_values_names) {
                if(possible_names_tmp == possible_names) {
                    continue;
                }
                possible_names_tmp.erase(to_eliminate);
            }
        }
        enumerate = (enumerate + 1) % possible_values_names.size();
        satisfied = true;
        for(auto possible_names: possible_values_names) {
            if(1 != possible_names.size()) {
                satisfied = false;
                break;
            }
        }
    }

    std::vector<uint64_t> departure_indices;
    auto idx = 0U;
    for(auto field_idx: possible_values_names) {
        if((*field_idx.begin()).rfind("departure", 0) == 0) {
            departure_indices.push_back(idx);
        }
        idx++;
    }


    auto departue_value = 1ULL;
    for(auto idx: departure_indices) {
        departue_value *= my_ticket[idx];
    }
    return departue_value;
}
