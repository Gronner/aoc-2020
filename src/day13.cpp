#include "days.hpp"

#include <algorithm>
#include <climits>
#include <cstdint>
#include <iostream>
#include <utility>
#include "parsing.hpp"

uint64_t bus_travel(std::vector<std::string> input_data) {
    /*
    input_data = {
        "",
        "17,x,13,19"
    };
    */
    //uint64_t earliest_departure = std::stoll(input_data[0]);
    const auto schedule = aoc::split_on_delimiter(input_data[1], ",");

    auto schedule_tmp = schedule;
    std::vector<uint64_t> schedule_times;
    schedule_tmp.erase(std::remove(schedule_tmp.begin(), schedule_tmp.end(), "x"), schedule_tmp.end());
    std::transform(schedule_tmp.begin(), schedule_tmp.end(), std::back_inserter(schedule_times), [](std::string s) -> unsigned int { return std::stoi(s); });
    auto biggest_id = *std::max_element(schedule_times.begin(), schedule_times.end());
    auto index_biggest_id = std::find(schedule.begin(), schedule.end(), std::to_string(biggest_id)) - schedule.begin();

    uint64_t start_search_at = 247'086'664'200'000;
    //const uint64_t first_bus = std::stoll(schedule[0]);
    start_search_at = start_search_at + (biggest_id - (start_search_at % biggest_id )) - index_biggest_id;
    auto found_counter = 0U;
    for(auto departure_time = start_search_at; departure_time < ULLONG_MAX; departure_time += biggest_id) {
        for(auto bus = 0ULL; bus < schedule.size(); ++bus) {
            uint64_t bus_id;
            if(schedule[bus] != "x") {
                bus_id = std::stoll(schedule[bus]);
            } else {
                found_counter++;
                continue;
            }
            if(0 == (departure_time + bus) % bus_id) {
                found_counter++;
            }
        }
        if(found_counter == schedule.size()) {
            return departure_time;
        }
        found_counter = 0;
    }
    return 0;
}

using busses_t = std::vector<std::pair<int64_t, int64_t>>;
uint64_t chinese_remainder_solve(busses_t busses) {
    // Using https://en.wikipedia.org/wiki/Chinese_remainder_theorem#Search_by_sieving
    auto time = busses[0].second;
    auto increment = busses[0].first;

    for(auto bus = busses.begin() + 1; bus != busses.end(); ++bus) {
        while(1) {
            if((time % (*bus).first) == ((*bus).second)) {
                break;
            }

            time += increment;
        }
        increment *= (*bus).first;
    }
    return time;
}

uint64_t bus_travel_crt(std::vector<std::string> input_data) {
    const auto schedule = aoc::split_on_delimiter(input_data[1], ",");
    busses_t busses;
    int64_t enumerate = 0;
    for(auto bus: schedule) {
        if(bus == "x") {
            enumerate++;
            continue;
        }
        int64_t modulus = std::stoll(bus);
        int64_t remainder = (modulus - enumerate % modulus) % modulus;
        busses.push_back(std::make_pair(modulus, remainder));
        enumerate++;
    }
    std::sort(busses.begin(), busses.end(), [](auto a, auto b) { return a.first > b.first; });

    return chinese_remainder_solve(busses);
}
