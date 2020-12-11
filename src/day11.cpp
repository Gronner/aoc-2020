#include "days.hpp"

#include <algorithm>

unsigned int musical_chairs(std::vector<std::string> seat_layout) {
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

                const std::vector<std::pair<int, int>> vectors = { 
                    std::make_pair(1,0),
                    std::make_pair(1,1),
                    std::make_pair(0,1),
                    std::make_pair(-1,1),
                    std::make_pair(-1,0),
                    std::make_pair(-1,-1),
                    std::make_pair(0,-1),
                    std::make_pair(1,-1)
                };
                
                for(auto direction: vectors) {
                    int distance_x = direction.first;
                    int distance_y = direction.second;
                    while(seat_layout[row + distance_y].at(place + distance_x) == '.') {
                        distance_x += direction.first;
                        distance_y += direction.second;
                    }

                    if(seat_layout[row + distance_y].at(place + distance_x) == '#') {
                        adjacent_taken_seats++;
                    }
                }

                if(5 <= adjacent_taken_seats) {
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
