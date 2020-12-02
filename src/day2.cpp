#include "day2.hpp"

#include <regex>
#include <iostream>
#include <string>

#include "aoc_input.hpp"

void day2() {
    auto input = aoc::read_input_linewise("");

    unsigned int found_matches = 0;

    for(auto pwpol: input) {
        std::regex policy_reg("(\\d*)-(\\d*) ([a-z]): (\\w*)");
        std::smatch matcher;
        std::regex_match(pwpol, matcher, policy_reg);
        
        int position1 = std::stoi(matcher[1]) - 1;
        int position2 = std::stoi(matcher[2]) - 1;
        std::string password = matcher[4];
        std::cout << position1 << " " << position2 << " " << matcher[3] << " " << password[position1] << password[position2] << std::endl;

        if((matcher[3] == password[position1]) ||  (matcher[3] == password[position2])) {
            if (password[position1] != password[position2]) {
                found_matches++;
            }
        }
    }

    std::cout << found_matches << std::endl;
}
