set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Werror")

set(SOURCES
    main.cpp)

add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY} STATIC ${SOURCES})
