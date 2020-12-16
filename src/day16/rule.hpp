#pragma once

#include <cstdint>
#include <string>

class Rule {
    private:
        std::string name;
        uint64_t min_1;
        uint64_t max_1;
        uint64_t min_2;
        uint64_t max_2;
        Rule(std::string name, uint64_t min_1, uint64_t max_1, uint64_t min_2, uint64_t max_2);
    public:
        static Rule from_string(std::string input);
        std::string get_name() const;
        bool is_fullfilled(uint64_t value);
};
