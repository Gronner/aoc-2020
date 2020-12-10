#include "days.hpp"

#include <iostream>

#include <algorithm>

static unsigned int to_number(std::string& input) {
    return std::stoul(input);
}

unsigned long long adapter_chaining(std::vector<std::string> input_data) {
    std::vector<unsigned int> adapters;
    std::transform(input_data.begin(), input_data.end(), std::back_inserter(adapters), to_number);
    std::sort(adapters.begin(), adapters.end());
    unsigned int device_rating = adapters.back() + 3;
    adapters.push_back(device_rating);
    adapters.insert(adapters.begin(), 0);

    std::vector<unsigned int> differentials;

    for(auto adapter = adapters.begin() + 1; adapter != adapters.end(); adapter++) {
        differentials.push_back(*adapter - *(adapter - 1));
    }

    std::vector<unsigned int> gap_sizes;
    unsigned int jumped = 0;
    for(auto differential: differentials) {
        if(differential == 1) {
            jumped++;
        } else if(differential == 3) {
            gap_sizes.push_back(jumped);
            jumped = 0;
        }
    }
    gap_sizes.push_back(jumped);

    unsigned long long product = 1;
    for(auto gap_size: gap_sizes) {
        switch(gap_size) {
            case 2: product = product * 2;
                      break;
            case 3: product = product * 4;
                      break;
            case 4: product = product * 7;
                      break;
            default: break;
        }
    }

    return product;
}
