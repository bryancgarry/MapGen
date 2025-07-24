#include "MapGen.hpp"

int main(int argc, char* argv[]) {
    int GRID_SIZE = 30;
    int WINDOOW_WIDTH = 800;
    int WINDOW_HEIGHT = 600;

    MapGen app(GRID_SIZE, WINDOOW_WIDTH, WINDOW_HEIGHT);
    app.run();
    return 0;
}

