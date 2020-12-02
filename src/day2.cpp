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
        std::smatch m;
        std::regex_match(pwpol, m, policy_reg);
        
        int min_occurence = std::stoi(m[1]);
        int max_occurence = std::stoi(m[2]);
        std::string password = m[4];

        int counter = 0;
        for(auto c: password) {
            if(c == m[3]) {
                counter++;
            }
        }
        
        if(counter >= min_occurence && counter <= max_occurence) {
            found_matches++;
        }
    }

    std::cout << found_matches << std::endl;
}
