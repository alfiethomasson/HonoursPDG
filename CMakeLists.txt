cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

# set the project name
project(ProceduralDungeonGeneration VERSION 1.0)

# add the executable
file(GLOB_RECURSE SOURCES App/*.cpp App/*.h)
add_executable(Application ${SOURCES})