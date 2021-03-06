set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-std=c++20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wpedantic -Werror -O3")

set(SOURCES
    main.cpp
    aoc_input.cpp
    parsing.cpp
    day1.cpp
    day2.cpp
    day3.cpp
    day4/passport.cpp
    day4/rules.cpp
    day4/day4.cpp
    day5.cpp
    day6/travel_group.cpp
    day6/day6.cpp
    day7/bag_type.cpp
    day7/day7.cpp
    day8.cpp
    day9.cpp
    day10.cpp
    day11.cpp
    day12/ship.cpp
    day12/day12.cpp
    day13.cpp
    day14.cpp
    day16/rule.cpp
    day16/day16.cpp
    day17.cpp
    day18.cpp
    day19.cpp
    day20/tile.cpp
    day20/day20.cpp
    day21.cpp
    day22.cpp
    day23_alt.cpp
    day24/floor_tile.cpp
    day24/day24.cpp
    day25/encryption_breaker.cpp
    day25/day25.cpp)

add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY} STATIC ${SOURCES})
