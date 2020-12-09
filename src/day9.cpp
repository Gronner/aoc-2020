#include "days.hpp"

#include <iostream>
#include <numeric>

static bool sum_of_parts(unsigned long long current_value, std::vector<unsigned long long> ring_puffer) {
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

std::pair<unsigned long long, auto> xmas_breaker(std::vector<std::string> input_data, unsigned int ring_length) {
    auto input_pos = input_data.cbegin();
    
    std::vector<unsigned long long> ring_puffer;
    for(unsigned int i = 0; i < ring_length; ++i) {
        ring_puffer.push_back(std::stoull(*input_pos));
        input_pos++;
    }
    std::reverse(ring_puffer.begin(), ring_puffer.end());
    unsigned long long current_value;
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

static unsigned long long to_number(std::string& input) {
    return std::stoull(input);
}

static unsigned long long get_sum(const size_t sliding_window_size, const std::vector<unsigned long long> input, unsigned long long encryption_cipher) {
    auto window_begin = input.begin();
    do { 
        unsigned long long sum = std::accumulate(window_begin, window_begin + sliding_window_size, 0);
        if(encryption_cipher == sum) {
            auto max_val = *std::max_element(window_begin, window_begin + sliding_window_size);
            auto min_val = *std::min_element(window_begin, window_begin + sliding_window_size);
            return max_val + min_val;
        }
        window_begin++;
    } while((window_begin + 2) != input.end());
    return 0;
}

unsigned long long xmas_breaker_part2(std::vector<std::string> input_data, unsigned ring_length) {
    auto first_break = xmas_breaker(input_data, ring_length);
    auto encryption_cipher = first_break.first;
    auto position_first_break = first_break.second;

    std::vector<unsigned long long> values;
    std::transform(input_data.begin(), input_data.begin() + position_first_break, std::back_inserter(values), to_number);
    size_t sliding_window_size = 3;
    unsigned long long sum;
    do {
        sum = get_sum(sliding_window_size, values, encryption_cipher);
        sliding_window_size++;
        std::cout << sliding_window_size << std::endl;
    } while((0 == sum) && (sliding_window_size <= values.size()));

    return sum;
}
