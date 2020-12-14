#include "days.hpp"

#include <map>
#include <iostream>

#include "parsing.hpp"

uint64_t dock_decoding(std::vector<std::string> input_data) {
    std::map<uint64_t, uint64_t> memory;
    std::string mask = "";
    for(const auto line: input_data) {
        auto entry = aoc::split_on_delimiter(line, " = ");
        if("mask" == entry[0]) {
            mask = entry[1];
            continue;
        } 
        auto address = aoc::grab_information(entry[0], "mem\\[(\\d*)\\]");
        uint64_t address_value = std::stoll(address[1]);
        uint64_t mem_value = std::stoll(entry[1]);

        uint64_t bit_counter = 0;
        for(auto bit = mask.rbegin(); bit != mask.rend(); ++bit) {
            if(*bit == 'X') {
                bit_counter ++;
                continue;
            }
            if(*bit == '0') {
                mem_value &= ~(1ULL << bit_counter);
            } else {
                mem_value |= 1ULL << bit_counter;
            }
            bit_counter++;
        }
        memory[address_value] = mem_value;
    }
    uint64_t sum = 0;
    for(auto value: memory) {
        sum += value.second;
    }
    return sum;
}
