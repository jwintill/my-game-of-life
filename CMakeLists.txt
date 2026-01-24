cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(GameOfLife
    src/main.cpp
    src/Grid.cpp
)

target_link_libraries(GameOfLife PRIVATE SDL2::SDL2)