cmake_minimum_required(VERSION 3.15)
project(SimpleSDL2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SimpleSDL2 src/main.cpp)
target_link_libraries(SimpleSDL2 ${SDL2_LIBRARIES})
