#include "days.hpp"

#include <tuple>

static auto normalize_customs_answer_layout(const std::vector<std::string> input_data) {
    std::vector<std::tuple<std::string, unsigned int>> normalized_customs_answers;
    std::string temporary_answer = "";
    std::tuple<std::string, unsigned int> group_information;
    unsigned int group_members = 0;
    for(auto line: input_data) {
        if(line.size() == 0) {
            normalized_customs_answers.push_back(
                    std::make_tuple(temporary_answer, group_members)
                    );
            temporary_answer.clear();
            group_members = 0;
            continue;
        }
        temporary_answer += line;
        group_members++;
    }
    normalized_customs_answers.push_back(
                std::make_tuple(temporary_answer, group_members)
                );
    return normalized_customs_answers;
}

unsigned int count_customs_answers(std::vector<std::string> input_data) {
    auto normalized_customs_answers = normalize_customs_answer_layout(input_data);
    unsigned int answer_count = 0;

    for(auto answers: normalized_customs_answers) {
        std::sort(std::get<0>(answers).begin(), std::get<0>(answers).end());

        char letter = std::get<0>(answers).at(0);
        unsigned int group_answers = 0;

        for(auto answer: std::get<0>(answers)) {
            if(letter != answer) {

                if(group_answers == std::get<1>(answers)) {
                    answer_count += 1;
                }

                group_answers = 0;
                letter = answer;
            }
            group_answers++;
        }
        if(group_answers == std::get<1>(answers)) {
            answer_count+= 1;
        }
    }
    return answer_count;
}
