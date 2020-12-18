#include "days.hpp"

template<typename T>
static auto get_index(const std::vector<T> vec, const T value) {
    return std::distance(vec.cbegin(), std::find(vec.cbegin(), vec.cend(), value));
}

template<typename T>
static auto pop(std::vector<T>& vec) {
    const auto tmp = vec.back();
    vec.pop_back();
    return tmp;
}

static const std::vector<char> operators{'*' , '+'};
static bool is_higher_precedence(const char token1, const char token2 ) {
    return get_index(operators, token1) <= get_index(operators, token2);
}

static bool is_operator(const char token) {
    return operators.end() != std::find(operators.begin(), operators.end(), token);
}

static bool is_digid(const char token) {
    return '0' <= token && token <= '9';
}

static std::vector<char> shunting_yard(const std::string line) {
    static const std::vector<char> operators{'*' , '+'};
    std::vector<char> output_queue;
    std::vector<char> operator_queue;
    for(const auto token: line) {
        if(is_digid(token)) {
            output_queue.push_back(token);
        } else if(is_operator(token)) {
            while(!operator_queue.empty() && is_higher_precedence(token, operator_queue.back()) && '(' != operator_queue.back()) {
                output_queue.push_back(pop(operator_queue));
            }
            operator_queue.push_back(token);
        } else if('(' == token) {
            operator_queue.push_back(token);
        } else if(')' == token) {
            while('(' != operator_queue.back()) {
                output_queue.push_back(pop(operator_queue));
            }
            if('(' == operator_queue.back()) {
                operator_queue.pop_back();
            }
        }
    }
    while(!operator_queue.empty()) {
        output_queue.push_back(pop(operator_queue));
    }
    return output_queue;
}

static uint64_t compute_postfix(const std::vector<char> postfix_notation) {
    std::vector<uint64_t> stack;
    for(const auto token: postfix_notation) {
        if('0' <= token && token <= '9') {
            stack.push_back(token - '0');
        } else {
            const auto val1 = stack.back();
            stack.pop_back();
            const auto val2 = stack.back();
            stack.pop_back();
            switch(token) {
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

uint64_t homework(const input_t input_data) {
    uint64_t sum = 0;
    for(const auto line: input_data) {
        const auto postfix_notation = shunting_yard(line);
        sum += compute_postfix(postfix_notation);
    }
    return sum;
}
