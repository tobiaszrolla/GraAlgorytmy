cmake_minimum_required(VERSION 3.10)
project(graph_algorithms)

set (CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

include_directories(${SFML_INCLUDE_DIR})

add_library(warcaby_lib src/warcaby.cpp src/plansza.cpp)

target_link_libraries(warcaby_lib sfml-graphics sfml-window sfml-system)

add_executable(gra "src/main.cpp")

target_link_libraries(gra warcaby_lib sfml-graphics sfml-window sfml-system)
