set(BINARY ${CMAKE_PROJECT_NAME}_test)

set(TEST_SOURCES
    main_test.cpp
    day1_tests.cpp
    day2_tests.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})
target_compile_definitions(${BINARY} PUBLIC TEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME} gtest)
