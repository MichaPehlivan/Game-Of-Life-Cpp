cmake_minimum_required(VERSION 3.0.0)
project(game_of_life VERSION 0.1.0)

add_executable(game_of_life src/main.cpp src/board.cpp src/board.h)

target_link_libraries(game_of_life SDL2)