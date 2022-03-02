cmake_minimum_required(VERSION 3.9)
add_subdirectory(src/generator)
add_subdirectory(src/utils)

target_include_directories(generator PUBLIC include)
target_include_directories(utils PUBLIC include)