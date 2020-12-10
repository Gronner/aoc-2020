#include "days.hpp"


#include <algorithm>
#include <cstdint>

static uint32_t to_number(const std::string& input) {
    return std::stoul(input);
}

static std::vector<uint32_t> chain_adapters(const std::vector<std::string> input_data) {
    std::vector<uint32_t> adapters;
    std::transform(input_data.begin(), input_data.end(), std::back_inserter(adapters), to_number);
    std::sort(adapters.begin(), adapters.end());
    const uint32_t device_rating = adapters.back() + 3;
    adapters.push_back(device_rating);
    adapters.insert(adapters.begin(), 0);
    return adapters;
}


static std::vector<uint32_t> compute_differentials(const std::vector<uint32_t> adapters) {
    std::vector<uint32_t> differentials;
    for(auto adapter = adapters.cbegin() + 1; adapter != adapters.cend(); adapter++) {
        differentials.push_back(*adapter - *(adapter - 1));
    }
    return differentials;
}

static std::vector<uint32_t> count_jumpable_adapters(const std::vector<uint32_t> differentials) {
    std::vector<uint32_t> jumpables;
    uint32_t jumpable = 0;
    for(const auto differential: differentials) {
        if(differential == 1) {
            jumpable++;
        } else if(differential == 3) {
            jumpables.push_back(jumpable);
            jumpable = 0;
        }
    }
    jumpables.push_back(jumpable);
    return jumpables;
}

static constexpr uint32_t get_jumpable_factor(const uint32_t jumpable_adapters) {
    switch(jumpable_adapters) {
        case 2: return 2;
        case 3: return 4;
        case 4: return 7;
        default: return 1;
    };
}

static uint64_t determine_possible_chains(const std::vector<uint32_t> jumpable_adapter_counts) {
    uint64_t product = 1;
    for(const auto jumpable_adapters: jumpable_adapter_counts) {
        product *= get_jumpable_factor(jumpable_adapters);
    }
    return product;
}

uint64_t adapter_chaining(const std::vector<std::string> input_data) {
    const auto adapters = chain_adapters(input_data);
    const auto differentials = compute_differentials(adapters);
    const auto jumpables = count_jumpable_adapters(differentials);
    return determine_possible_chains(jumpables);
}
