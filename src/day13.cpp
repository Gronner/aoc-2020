#include "days.hpp"

#include <iostream>
#include "parsing.hpp"

unsigned int bus_travel(std::vector<std::string> input_data) {
    unsigned int earliest_departure = std::stoi(input_data[0]);
    auto schedule = aoc::split_on_delimiter(input_data[1], ",");
    std::vector<unsigned int> schedule_times;
    schedule.erase(std::remove(schedule.begin(), schedule.end(), "x"), schedule.end());
    std::transform(schedule.begin(), schedule.end(), std::back_inserter(schedule_times), [](std::string s) -> unsigned int { return std::stoi(s); });
    unsigned int minimal_departure = 99999999;
    unsigned int fastest_bus = 0;
    for(auto schedule_time: schedule_times) {
        auto next_departure = schedule_time - (earliest_departure % schedule_time);
        if(minimal_departure > next_departure) {
            minimal_departure = next_departure;
            fastest_bus = schedule_time;
        }
    }
    return minimal_departure * fastest_bus;
}
