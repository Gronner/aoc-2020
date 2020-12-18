#include "days.hpp"

#include <iostream>

uint64_t recursive_math(std::string::iterator& begin, const std::string::iterator end) {
    uint64_t value = 0;
    char next_operation = 'X';
    while(begin != end) {
        if('(' == *begin) {
            begin++;
            if('+' == next_operation) {
                value += recursive_math(begin, end);
            } else if('*' == next_operation) {
                value *= recursive_math(begin, end);
            } else {
                value = recursive_math(begin, end);
            }
        } else if(' ' == *begin) {
            begin++;
        } else if('+' == *begin) {
            begin++;
            next_operation = '+';
        } else if('*' == *begin) {
            begin++;
            next_operation = '*';
        } else if(')' == *begin) {
            begin++;
            return value;
        } else {
            uint64_t current_digit = (*begin) - '0';
            begin++;
            if('+' == next_operation) {
                value += current_digit;
            } else if('*' == next_operation) {
                value *= current_digit;
            } else {
                value = current_digit;
            }
        }

    }
    return value;
}

uint64_t homework(std::vector<std::string> input_data) {
    uint64_t sum = 0;
    for(auto line: input_data) {
        auto start = line.begin();
        auto value = recursive_math(start, line.end());
        sum += value;
    }
    return sum;
}
