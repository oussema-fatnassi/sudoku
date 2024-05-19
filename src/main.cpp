#include <raylib.h>
#include <iostream>
#include "gui.hpp"
#include "menu.hpp"

int main() {
    Color darkGreen = Color{20, 160, 133, 255};

    const int screenWidth = 640;
    const int screenHeight = 1050;

    InitWindow(screenWidth, screenHeight, "Sudoku");
    SetTargetFPS(60);

    GUI sudokuGUI;
    Menu menu;
    sudokuGUI.menu = &menu;  // Link GUI and Menu
    menu.setGUI(&sudokuGUI); // Link Menu and GUI


    while (!WindowShouldClose()) {
        std::cout << "Current State: " << menu.getCurrentState() << std::endl;
        sudokuGUI.update();
        BeginDrawing();
        ClearBackground(darkGreen);
        menu.drawMenu(); 
        EndDrawing();
    }
    CloseWindow();
    return 0;
}