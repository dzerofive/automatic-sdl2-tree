cmake_minimum_required(VERSION 3.1)

project(Loliconic)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(core lib)
target_link_libraries(${PROJECT_NAME} core SDL2)