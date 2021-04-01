cmake_minimum_required(VERSION 3.17)
project(IDZ_2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic ")

find_library(PTHREAD_LIBRARY pthread)

# Sequential
add_library(sequential STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/src/sequential_counter.c)

target_include_directories(sequential PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Parallel
add_library(parallel SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parallel_counter.c)

target_include_directories(parallel PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(parallel PUBLIC
        ${PTHREAD_LIBRARY})

# Main
add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
        )

target_link_libraries(main PUBLIC
        sequential
        parallel)

target_include_directories(main PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

#Tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest)
enable_testing()

## Sequential
add_executable(tests_seq tests/sequential.cpp)

target_include_directories(tests_seq
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(tests_seq
        gtest_main
        sequential)

## Parallel
add_executable(tests_par tests/parallel.cpp)

target_include_directories(tests_par
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(tests_par
        gtest_main
        parallel)

# Coverage
## Sequential
target_compile_options(sequential PRIVATE
        --coverage
        )
target_link_libraries(sequential INTERFACE --coverage)

## Parallel
target_compile_options(parallel PRIVATE
        -lcov
        #[[--coverage]]
        )
target_link_libraries(parallel INTERFACE --coverage)
