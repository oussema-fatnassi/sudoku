#include <raylib.h>
#include <iostream>
#include "grid.hpp"
#include "cell.hpp"
#include "gui.hpp"

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};

    const int screenWidth = 640;
    const int screenHeight = 1050;

    InitWindow(screenWidth, screenHeight, "Sudoku");
    SetTargetFPS(60);

    // Grid sudokuGrid = Grid();
    GUI sudokuGUI = GUI();
    
    while (!WindowShouldClose())
    {
        // sudokuGrid.update();
        BeginDrawing();
        sudokuGUI.update();
        sudokuGUI.draw();
        ClearBackground(darkGreen);
        // sudokuGrid.drawGrid();
        EndDrawing();
        (sudokuGrid.getCell(0, 0)).setValue(1);
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << (sudokuGrid.getCell(i, j)).getValue() << " ";
        }
        cout << endl;
    }
    CloseWindow();
    return 0;
}