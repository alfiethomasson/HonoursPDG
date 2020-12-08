cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

# set the project name
project(ProceduralDungeonGeneration VERSION 1.0)

add_subdirectory("sfml")
set(SFML_INCS "sfml/include")
link_directories("${CMAKE_BINARY_DIR}/sfml/lib")

# add the executable
file(GLOB_RECURSE SOURCES App/*.cpp App/*.h)
add_executable(Application ${SOURCES})
target_include_directories(Application PRIVATE ${SFML_INCS})
target_link_libraries(Application sfml-graphics)