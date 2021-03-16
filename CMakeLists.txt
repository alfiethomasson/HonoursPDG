cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

# set the project name
project(ProceduralDungeonGeneration VERSION 1.0)

add_subdirectory("lib/sfml")
set(SFML "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

file(GLOB_RECURSE res res/*.jpg res/*.png res/*.ttf)
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

# add the executable
file(GLOB_RECURSE SOURCES App/*.cpp App/*.h App/*.hpp)
add_executable(DungeonGenerator ${SOURCES})
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_include_directories(DungeonGenerator SYSTEM PRIVATE ${SFML} "D:/Github/imgui" "D:/Github/imgui-sfml")
set(EXECUTABLES ${EXECUTABLES} DungeonGenerator)

foreach (exe ${EXECUTABLES})

  #Add all SFML libs.
  target_link_libraries(${exe}
    optimized sfml-graphics debug sfml-graphics-d
    optimized sfml-window debug sfml-window-d
    optimized sfml-system debug sfml-system-d
    optimized sfml-main
${OPENGL_LIBRARIES}
)
endforeach ()