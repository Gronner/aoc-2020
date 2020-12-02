#include "day2.hpp"

#include <iostream>
#include <string>

#include "aoc_input.hpp"
#include "parsing.hpp"

void day2() {
    auto input = aoc::read_input_linewise("");

    unsigned int found_matches = 0;

    for(auto pwpol: input) {
        std::string expression = "(\\d*)-(\\d*) ([a-z]): (\\w*)";
        auto matched_information = aoc::grab_information(pwpol, expression);

        int position1 = std::stoi(matched_information[1]) - 1;
        int position2 = std::stoi(matched_information[2]) - 1;
        std::string password = matched_information[4];

        if((matched_information[3].at(0) == password[position1]) ||  (matched_information[3].at(0) == password[position2])) {
            if (password[position1] != password[position2]) {
                found_matches++;
            }
        }
    }

    std::cout << found_matches << std::endl;
}
