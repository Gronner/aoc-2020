#include "day25/encryption_breaker.hpp"

#include <iostream>

EncryptionBreaker::EncryptionBreaker(uint64_t loop_number) 
    : loop_number(loop_number) {}

uint64_t EncryptionBreaker::compute_key(const uint64_t subject_number) const {
    uint64_t start_value = 1ULL;
    for(auto round = 0ULL; round < loop_number; ++round) {
        start_value *= subject_number;
        start_value %= 20201227ULL;
    }
    return start_value;
}
