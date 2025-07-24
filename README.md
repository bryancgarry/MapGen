# MapGen
A C++ tool for procedurally generating fantasy-style maps using Voronoi tessellation. Ideal for RPG campaigns, worldbuilding, or creative map design.

## Necessary Dependencies
- SDL2

## Features Implemented
- Grid-based jittered point generation
- Interactive SDL window with render loop
- Visual rendering of grid points to the screen
- In-progress implementation of Delaunay triangulation (Bowyer-Watson algorithm)
  - Super triangle generation
  - Edge and triangle structs with robust comparison operators
  - Circumcircle test for point insertion
- Framework set up for polygonal region generation

## Build Instructions
1. Install SDL2 on your system (using a package manager like `brew` for example).
2. Clone this repository.
3. Build using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ./MapGen