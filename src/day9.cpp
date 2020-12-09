#include "days.hpp"

#include <algorithm>
#include <cstdint>
#include <numeric>

static bool sum_of_parts(uint64_t current_value, std::vector<uint64_t> ring_puffer) {
    for(auto value1: ring_puffer) {
        for(auto value2: ring_puffer) {
            if(value1 == value2) {
                continue;
            }
            if(current_value == (value1 + value2)) {
                return true;
            }
        }
    }
    return false;
}

std::pair<uint64_t, auto> xmas_breaker(std::vector<std::string> input_data, uint32_t ring_length) {
    auto input_pos = input_data.cbegin();
    
    std::vector<uint64_t> ring_puffer;
    for(uint32_t i = 0; i < ring_length; ++i) {
        ring_puffer.push_back(std::stoull(*input_pos));
        input_pos++;
    }
    std::reverse(ring_puffer.begin(), ring_puffer.end());
    uint64_t current_value;
    do {
         current_value = std::stoull(*input_pos);
         if(!sum_of_parts(current_value, ring_puffer)) {
             break;
         }
         ring_puffer.insert(ring_puffer.begin(), current_value);
         ring_puffer.pop_back();
         input_pos++;
        
    } while(input_pos != input_data.end());
    return std::make_pair(current_value, input_pos - input_data.begin());
}

static uint64_t to_number(std::string& input) {
    return std::stoull(input);
}

static uint64_t get_sum(const size_t sliding_window_size, const std::vector<uint64_t> input, uint64_t encryption_cipher) {
    auto window_begin = input.begin();
    do { 
        uint64_t sum = std::accumulate(window_begin, window_begin + sliding_window_size, 0);
        if(encryption_cipher == sum) {
            auto max_val = *std::max_element(window_begin, window_begin + sliding_window_size);
            auto min_val = *std::min_element(window_begin, window_begin + sliding_window_size);
            return max_val + min_val;
        }
        window_begin++;
    } while((window_begin + 2) != input.end());
    return 0;
}

uint64_t xmas_breaker_part2(std::vector<std::string> input_data, uint32_t ring_length) {
    const auto first_break = xmas_breaker(input_data, ring_length);
    const auto encryption_cipher = first_break.first;
    const auto position_first_break = first_break.second;

    std::vector<uint64_t> values;
    std::transform(input_data.begin(), input_data.begin() + position_first_break, std::back_inserter(values), to_number);
    size_t sliding_window_size = 3;
    uint64_t sum;
    do {
        sum = get_sum(sliding_window_size, values, encryption_cipher);
        sliding_window_size++;
    } while((0 == sum) && (sliding_window_size <= values.size()));

    return sum;
}
