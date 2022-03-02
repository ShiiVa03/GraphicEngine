cmake_minimum_required(VERSION 3.9)

add_executable(generator main.cpp plane.cpp)

target_link_libraries(generator utils)
 
