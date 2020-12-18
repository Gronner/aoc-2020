#include "days.hpp"

#include <iostream>

#include "aoc_input.hpp"
#include "parsing.hpp"

unsigned int passwort_policy_matches(input_t input_data) {
    unsigned int found_matches = 0;

    for(auto pwpol: input_data) {
        const std::string expression = "(\\d*)-(\\d*) ([a-z]): (\\w*)";
        const auto matched_information = aoc::grab_information(pwpol, expression);

        const int position1 = std::stoi(matched_information[1]) - 1;
        const int position2 = std::stoi(matched_information[2]) - 1;
        const char symbol = matched_information[3].at(0);
        const std::string password = matched_information[4];

        if((symbol == password[position1]) || (symbol == password[position2])) {
            if (password[position1] != password[position2]) {
                found_matches++;
            }
        }
    }
    return found_matches;
}
