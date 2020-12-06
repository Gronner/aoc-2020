#pragma once

#include <string>

class TravelGroup {
    private:
        const unsigned int member_count;
        const std::string answers;
    public:
        TravelGroup(const unsigned int member_count, const std::string answers);
        unsigned int get_unique_answers() const;
        unsigned int get_common_answers() const;
};
