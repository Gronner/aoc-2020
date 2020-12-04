#pragma once

#include <string>

template<size_t idx>
constexpr unsigned int const_hash(const char* input) {
    unsigned int hash_value = 0;
    for(unsigned int i = 0; i < idx; i++) {
        hash_value += int(input[i]); 
    }
    return hash_value;
}
