cmake_minimum_required(VERSION 3.15)
project(MapGen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(MapGen
    src/main.cpp
    src/MapGen.cpp
    src/Map.cpp
    src/MathUtils.cpp
)

target_link_libraries(MapGen ${SDL2_LIBRARIES})
