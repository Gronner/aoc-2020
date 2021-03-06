#include "travel_group.hpp"

#include <algorithm>
#include <set>

TravelGroup::TravelGroup(const unsigned int member_count, const std::string answers) :
    member_count(member_count), answers(answers) {}

unsigned int TravelGroup::get_unique_answers() const {
    const std::set<char> unique_answers(answers.begin(), answers.end());
    return unique_answers.size();
}

unsigned int TravelGroup::get_common_answers() const {
    const std::set<char> unique_answers(answers.begin(), answers.end());
    unsigned int common_answers = 0;
    for(auto letter: unique_answers) {
        const unsigned int answer_count = std::count(answers.begin(), answers.end(), letter);
        common_answers += member_count == answer_count ? 1 : 0;
    }
    return common_answers;
}
