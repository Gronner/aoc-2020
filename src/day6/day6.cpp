#include "days.hpp"

#include <tuple>

#include "day6/travel_group.hpp"

static auto retrieve_tarvel_groups(const input_t input_data) {
    std::vector<TravelGroup> travel_groups;
    std::string temporary_answer = "";

    unsigned int group_members = 0;
    for(auto line: input_data) {
        if(line.size() == 0) {
            TravelGroup travel_group(group_members, temporary_answer);
            travel_groups.push_back(travel_group);
            temporary_answer.clear();
            group_members = 0;
            continue;
        }
        temporary_answer += line;
        group_members++;
    }
    TravelGroup travel_group(group_members, temporary_answer);
    travel_groups.push_back(travel_group);
    return travel_groups;
}

unsigned int count_customs_answers(const input_t input_data) {
    const auto travel_groups  = retrieve_tarvel_groups(input_data);
    unsigned int answer_count = 0;

    for(const auto travel_group: travel_groups) {
        answer_count += travel_group.get_common_answers();
    }
    return answer_count;
}
