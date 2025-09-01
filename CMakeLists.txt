cmake_minimum_required(VERSION 3.15)
project(MapGen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# SDL2 setup
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Manually specify SDL2_gfx path
set(SDL2_GFX_INCLUDE_DIR /opt/homebrew/Cellar/sdl2_gfx/1.0.4/include)
set(SDL2_GFX_LIBRARY /opt/homebrew/Cellar/sdl2_gfx/1.0.4/lib/libSDL2_gfx.dylib)

include_directories(${SDL2_GFX_INCLUDE_DIR})

add_executable(MapGen
    src/main.cpp
    src/MapGen.cpp
    src/Map.cpp
    src/MathUtils.cpp
    src/Delaunay.cpp
)

target_link_libraries(MapGen ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARY})