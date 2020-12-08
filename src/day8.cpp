#include "days.hpp"

#include <utility>

#include <algorithm>
#include <exception>
#include <map>

#include "helpers.hpp"
#include "parsing.hpp"

using OpcodeList = std::vector<std::pair<std::string, int>>;

OpcodeList parse_opcodes(const std::vector<std::string> input_data) {
    OpcodeList opcode_list; 
    for(auto line: input_data) {
        const auto operations = aoc::grab_information(line, "(\\w{3}) ([+-]\\d*)");
        opcode_list.push_back(std::make_pair(operations[1], std::stoi(operations[2])));
    }
    return opcode_list;
}

static bool is_replaceable(std::pair<std::string, int> opcode) {
    if("nop" == opcode.first || "jmp" == opcode.first) {
        return true;
    }
    return false;
}

static std::pair<std::string, int> replace_opcode(std::pair<std::string, int> opcode) {
    if("nop" == opcode.first) {
        opcode.first = "jmp";
    } else {
        opcode.first = "nop";
    }
    return opcode;
}

static std::pair<bool, int> run_computer(const OpcodeList opcode_list) {
    std::map<int, bool> visited;
    int accumulator = 0;
    size_t pc = 0;
    bool success = false;
    while((pc != opcode_list.size()) && (visited.find(pc) == visited.end())) {
        size_t old_pc = pc;
        switch(const_hash<3>(opcode_list[pc].first.c_str())) {
            case const_hash<3>("nop"): pc++;
                                       break;
            case const_hash<3>("jmp"): pc += opcode_list[pc].second;
                                       break;
            case const_hash<3>("acc"): accumulator += opcode_list[pc].second;
                                       pc++;
                                       break;
            default: throw std::invalid_argument("Unkown opcode");
        }
        visited.insert(std::make_pair(old_pc, true));
    }
    if(pc == opcode_list.size()) {
        success = true;
    }
    return std::make_pair(success, accumulator);
}

int boot_sequence(const std::vector<std::string> input_data) {
    const auto opcode_list = parse_opcodes(input_data);
    
    auto op_iter = opcode_list.cbegin();

    while((op_iter = std::find_if(op_iter, opcode_list.cend(), is_replaceable)) != opcode_list.cend()) {
        auto tmp_ol(opcode_list);
        tmp_ol[op_iter - opcode_list.cbegin()] = replace_opcode(tmp_ol[op_iter - opcode_list.cbegin()]);
        auto result = run_computer(tmp_ol); 
        if(result.first) {
            return result.second;
        }
        op_iter++;
    }
    
    return 0;
}
