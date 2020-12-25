#pragma once

#include <cstdint>

class EncryptionBreaker {
    private:
        uint64_t subject_number;
    public:
        uint64_t loop_number;
        EncryptionBreaker(uint64_t loop_number);
        uint64_t compute_key(const uint64_t start_value) const;
        void up_loop_number();
};
