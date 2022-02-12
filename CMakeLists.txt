cmake_minimum_required(VERSION 3.21)
project(Lab4_Maze)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab4_Maze main.cpp PathfinderInterface.h Pathfinder.cpp Pathfinder.h)
