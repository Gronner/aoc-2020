#include "days.hpp"

#include <algorithm>
#include <iostream>

unsigned int musical_chairs(std::vector<std::string> seat_layout) {
    /*
    seat_layout  = {
        "L.LL.LL.LL",
        "LLLLLLL.LL",
        "L.L.L..L..",
        "LLLL.LL.LL",
        "L.LL.LL.LL",
        "L.LLLLL.LL",
        "..L.L.....",
        "LLLLLLLLLL",
        "L.LLLLLL.L",
        "L.LLLLL.LL"
    };
    */

    // First Round all seats get taken
    std::string extra_row(seat_layout[0].size(), '*');
    seat_layout.insert(seat_layout.begin(), extra_row);
    seat_layout.push_back(extra_row);
    for(auto& row: seat_layout) {
        std::replace(row.begin(), row.end(), 'L', '#');
        row.insert(row.begin(), '*');
        row.push_back('*');
    }

    auto seats_changed = 0;
    do {
        seats_changed = 0;
        auto seat_layout_tmp = seat_layout;
        for(auto row = 1U; row != seat_layout.size() - 1; ++row) {
            for(auto place = 1U; place != seat_layout[row].size() - 1; ++place) {
                auto adjacent_taken_seats = 0U;
                if(seat_layout[row].at(place) == '.') {
                    continue;
                }
                adjacent_taken_seats += std::count_if((*(seat_layout.begin() + row - 1)).begin() + place - 1,
                        (*(seat_layout.begin() + row - 1)).begin() + place + 2,
                        [](char c){ return '#' == c;});
                adjacent_taken_seats += (seat_layout[row].at(place + 1) == '#') ? 1 : 0;
                adjacent_taken_seats += (seat_layout[row].at(place - 1) == '#') ? 1 : 0;
                adjacent_taken_seats += std::count_if((*(seat_layout.begin() + row + 1)).begin() + place - 1,
                        (*(seat_layout.begin() + row + 1)).begin() + place + 2,
                        [](char c){ return '#'  == c;});
                if(4 <= adjacent_taken_seats) {
                    if('#' == seat_layout[row].at(place)) {
                        seat_layout_tmp[row][place] = 'L';
                        seats_changed++;
                    } 
                } 
                if(0 == adjacent_taken_seats) {
                    if('L' == seat_layout[row].at(place)) {
                        seat_layout_tmp[row][place] = '#';
                        seats_changed++;
                    }
                }
            }
        }
        seat_layout = seat_layout_tmp;
    } while(0 != seats_changed);

    unsigned int taken_seats = 0;
    for(auto row: seat_layout) {
        for(auto place: row) {
            if('#' == place) {
                taken_seats++;
            }
        }
    }

    return taken_seats;
}
