cmake_minimum_required(VERSION 3.17)
project(IDZ_2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic")

# Sequential
add_library(sequential STATIC
            ${CMAKE_CURRENT_SOURCE_DIR}/src/sequential_counter.c)

target_include_directories(sequential PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Main
add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
        )

target_link_libraries(main PUBLIC
        sequential)
target_include_directories(main PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)