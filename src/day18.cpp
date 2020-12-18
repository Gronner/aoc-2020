#include "days.hpp"

std::vector<char> shunting_yard(std::string line) {
    static std::vector<char> operators{'*' , '+'};
    std::vector<char> output_queue;
    std::vector<char> operator_queue;
    for(auto token: line) {
        if(token >= '0' && token <= '9') {
            output_queue.push_back(token);
        } else if(operators.end() != std::find(operators.begin(), operators.end(), token)) {
            while((0 != operator_queue.size()) && 
                (std::distance(operators.begin(), std::find(operators.begin(), operators.end(), token)) <= std::distance(operators.begin(), std::find(operators.begin(), operators.end(), operator_queue.back())) && '(' != operator_queue.back())) {
                output_queue.push_back(operator_queue.back());
                operator_queue.pop_back();
            }
            operator_queue.push_back(token);
        } else if('(' == token) {
            operator_queue.push_back(token);
        } else if(')' == token) {
            while('(' != operator_queue.back()) {
                auto tmp = operator_queue.back();
                output_queue.push_back(tmp);
                operator_queue.pop_back();
            }
            if('(' == operator_queue.back()) {
                operator_queue.pop_back();
            }
        }
    }
    while(0 != operator_queue.size()) {
        output_queue.push_back(operator_queue.back());
        operator_queue.pop_back();
    }
    return output_queue;
}

uint64_t compute_postfix(std::vector<char> postfix_notation) {
    std::vector<uint64_t> stack;
    for(auto c: postfix_notation) {
        if('0' <= c && c <= '9') {
            stack.push_back(c - '0');
        } else {
            auto val1 = stack.back();
            stack.pop_back();
            auto val2 = stack.back();
            stack.pop_back();
            switch(c) {
                case '+': stack.push_back(val1 + val2);
                          break;
                case '*': stack.push_back(val1 * val2);
                          break;
                default: break;
            }
        }
    }
    return stack.back();
}

uint64_t homework(std::vector<std::string> input_data) {
    /*
    input_data = {
        "1 + 2 * 3 + 4 * 5 + 6",
        "1 + (2 * 3) + (4 * (5 + 6))",
    };
    */
    uint64_t sum = 0;
    for(auto line: input_data) {
        auto postfix_notation = shunting_yard(line);
        sum += compute_postfix(postfix_notation);
    }
    return sum;
}
