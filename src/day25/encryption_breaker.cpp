#include "day25/encryption_breaker.hpp"

EncryptionBreaker::EncryptionBreaker(uint64_t loop_number) 
    : loop_number(loop_number) {}

uint64_t EncryptionBreaker::compute_key(const uint64_t subject_number) const {
    uint64_t start_value = 1ULL;
    for(auto round = 0ULL; round < loop_number; ++round) {
        start_value = transform(start_value, subject_number);
    }
    return start_value;
}

uint64_t transform(uint64_t value, const uint64_t subject_number) {
    value *= subject_number;
    value %= 20201227;
    return value;
}
