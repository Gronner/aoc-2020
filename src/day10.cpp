#include "days.hpp"

#include <iostream>

#include <algorithm>

static unsigned int to_number(std::string& input) {
    return std::stoul(input);
}

unsigned int adapter_chaining(std::vector<std::string> input_data) {
    std::vector<unsigned int> adapters;
    std::transform(input_data.begin(), input_data.end(), std::back_inserter(adapters), to_number);
    std::sort(adapters.begin(), adapters.end());
    unsigned int device_rating = adapters.back() + 3;
    adapters.push_back(device_rating);
    adapters.insert(adapters.begin(), 0);

    unsigned int one_jolt_diff_count = 0;
    unsigned int three_jolt_diff_count = 0;
    for(auto adapter = adapters.begin() + 1; adapter != adapters.end(); ++adapter) {
        std::cout << *adapter << std::endl;
       if(1 == *adapter - *(adapter - 1)) {
           one_jolt_diff_count++;
           continue;
       }
       if(3 == *adapter - *(adapter - 1)) {
           three_jolt_diff_count++;
           continue;
       }
    }

    return one_jolt_diff_count * three_jolt_diff_count;
}
