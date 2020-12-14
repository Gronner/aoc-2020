#include "days.hpp"

#include <map>
#include <iostream>

#include "parsing.hpp"

std::vector<std::string> generate_masks(std::string input_mask) {
    std::vector<size_t> x_indicies;
    size_t enumerate = 0;
    for(auto bit: input_mask) {
        if('X' == bit) {
            x_indicies.push_back(enumerate);
        }
        enumerate++;
    }
    const auto combinations = 1ULL << x_indicies.size();
    std::vector<std::string> masks(combinations, input_mask);
    auto stepsize = 2ULL;
    auto x_idx = x_indicies.begin();
    do {
        auto count = 1ULL;
        for(auto& mask: masks) {
            if(count < (stepsize / 2)) {
                mask[*x_idx] = '0';
            } else { 
                mask[*x_idx] = '1';
            }
            count = (count + 1) % stepsize;
        }
        x_idx++;
        stepsize <<= 1;
    } while(x_idx != x_indicies.end());
    return masks;
}

uint64_t dock_decoding(std::vector<std::string> input_data) {
    std::map<uint64_t, uint64_t> memory;
    std::vector<std::string> masks;
    std::string mask;
    for(const auto line: input_data) {
        auto entry = aoc::split_on_delimiter(line, " = ");
        if("mask" == entry[0]) {
            mask = entry[1];
            continue;
        } 
        auto address = aoc::grab_information(entry[0], "mem\\[(\\d*)\\]");
        std::string address_value = std::bitset<36>(std::stoll(address[1])).to_string();
        uint64_t mem_value = std::stoll(entry[1]);

        uint64_t bit_counter = 0;
        for(auto bit = mask.begin(); bit != mask.end(); ++bit) {
            if(*bit == '1') {
                address_value[bit_counter] = '1';
            } else if(*bit == 'X') {
                address_value[bit_counter] = 'X';
            }
            bit_counter++;
        }
        auto memory_addresses = generate_masks(address_value);
        for(auto memory_address: memory_addresses) {
            memory[std::stoll(memory_address, 0, 2)] = mem_value;
        }
    }
    uint64_t sum = 0;
    for(auto value: memory) {
        sum += value.second;
    }
    return sum;
}
