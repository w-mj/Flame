cmake_minimum_required(VERSION 3.10)
project(flame)

set(CMAKE_CXX_STANDARD 11)

add_executable(flame main.cpp Flame.cpp Flame.h )
target_link_libraries(flame SDL2 SDL2_ttf SDL2_image)
