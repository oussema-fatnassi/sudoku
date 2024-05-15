#include <raylib.h>
#include <iostream>
#include "grid.hpp"
#include "cell.hpp"

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};

    const int screenWidth = 640;
    const int screenHeight = 1050;

    InitWindow(screenWidth, screenHeight, "Sudoku");
    SetTargetFPS(60);

    Grid sudokuGrid = Grid();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);
        sudokuGrid.drawGrid();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}