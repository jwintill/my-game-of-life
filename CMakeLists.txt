cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 QUIET)

if (NOT SDL2_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.28.x
    )
    FetchContent_MakeAvailable(SDL2)

    set(SDL2_LIBRARIES SDL2::SDL2)
else()
    set(SDL2_LIBRARIES SDL2::SDL2)
endif()

add_executable(GameOfLife
    src/main.cpp
    src/Grid.cpp
)

if(WIN32)
    set(SDL2_LIBRARIES SDL2::SDL2main ${SDL2_LIBRARIES})
endif()

target_link_libraries(GameOfLife PRIVATE ${SDL2_LIBRARIES})