set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-std=c++20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wpedantic -Werror")

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
    day10.cpp)

add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY} STATIC ${SOURCES})
