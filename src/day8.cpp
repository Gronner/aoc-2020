#include "days.hpp"

#include <utility>

#include <algorithm>
#include <iostream>
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

int boot_sequence(std::vector<std::string> input_data) {
    auto opcode_list = parse_opcodes(input_data);
    
    OpcodeList::iterator op_iter = opcode_list.begin();

    while((op_iter = std::find_if(op_iter, opcode_list.end(), is_replaceable)) != opcode_list.end()) {
        OpcodeList tmp(opcode_list);
        tmp[op_iter - opcode_list.begin()] = replace_opcode(tmp[op_iter - opcode_list.begin()]);

        std::map<int, bool> visited;
        int accumulator = 0;
        size_t pc = 0;
        while((pc != input_data.size()) && (visited.find(pc) == visited.end())) {
            size_t old_pc = pc;
            switch(const_hash<3>(tmp[pc].first.c_str())) {
                case const_hash<3>("nop"): pc++;
                                           break;
                case const_hash<3>("jmp"): pc += tmp[pc].second;
                                           break;
                case const_hash<3>("acc"): accumulator += tmp[pc].second;
                                           pc++;
                                           break;
                default: return -1;
            }
            visited.insert(std::make_pair(old_pc, true));
        }
        if(pc == input_data.size()) {
            return accumulator;
        }
        op_iter++;
    }
    
    return 0;
}
