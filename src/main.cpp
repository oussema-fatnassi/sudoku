#include <raylib.h>
#include <iostream>
// #include "grid.hpp"
// #include "cell.hpp"
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

    // sudokuGUI.fillGrid();

    while (!WindowShouldClose()) {
        sudokuGUI.update();
        BeginDrawing();
        ClearBackground(darkGreen);
        menu.drawMenu();  // Use menu.drawMenu() instead of sudokuGUI.drawMainMenu()

        // Debug: print the current state
        std::cout << "Current State: " << menu.getCurrentState() << std::endl;

        // sudokuGUI.drawGame();
        EndDrawing();
        if (sudokuGUI.sudokuGrid.checkWinCondition()) {
            std::cout << "You win!" << std::endl;
            std::cin.get(); // Pause the program
            break;
        }
    }
    CloseWindow();
    return 0;
}
