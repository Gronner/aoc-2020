#pragma once

#include <string>

class TravelGroup {
    private:
        unsigned int member_count;
        std::string answers;
    public:
        TravelGroup(unsigned int member_count, std::string answers);
        unsigned int get_unique_answers();
        unsigned int get_common_answers();
};
