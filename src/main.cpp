#include <raylib.h>
#include <iostream>
#include "gui.hpp"
#include "menu.hpp"

int main() {
    Color darkGreen = Color{20, 160, 133, 255};         // Dark green color for the background

    const int screenWidth = 640;                        // Screen width and height
    const int screenHeight = 1050;

    InitWindow(screenWidth, screenHeight, "Sudoku");    // Initialize the window
    SetTargetFPS(60);

    GUI sudokuGUI;                                      // Create GUI and Menu objects
    Menu menu;
    sudokuGUI.menu = &menu;                             // Link GUI and Menu
    menu.setGUI(&sudokuGUI);                            // Link Menu and GUI


    while (!WindowShouldClose()) {                      // Main game loop
        sudokuGUI.update();
        BeginDrawing();
        ClearBackground(darkGreen);
        menu.drawMenu(); 
        EndDrawing();
    }
    CloseWindow();                                      // Close window and OpenGL context
    return 0;
}