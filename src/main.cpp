#include <raylib.h>
#include <iostream>
#include "grid.hpp"
#include "cell.hpp"
#include "gui.hpp"
#include "menu.hpp"

enum GameState {
    MAIN_MENU,
    GAMEPLAY,
    CREDITS,
    ABOUT
};

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};

    const int screenWidth = 640;
    const int screenHeight = 1050;

    InitWindow(screenWidth, screenHeight, "Sudoku");
    SetTargetFPS(60);

    GUI sudokuGUI = GUI();
    sudokuGUI.fillGrid();    
    Menu menu = Menu();
    GameState currentState = MAIN_MENU;

    while (!WindowShouldClose())
    {
        switch (currentState)
        {
            case MAIN_MENU:
                menu.update();
                if (menu.isStartPressed()) {
                    currentState = GAMEPLAY;
                } else if (menu.isCreditsPressed()) {
                    currentState = CREDITS;
                } else if (menu.isAboutPressed()) {
                    currentState = ABOUT;
                } else if (menu.isExitPressed()) {
                    CloseWindow();
                    return 0; // Quitter le jeu
                }
                break;

            case GAMEPLAY:
                // Ajoutez la logique de mise à jour du gameplay ici, si nécessaire
                break;

            case CREDITS:
                menu.updateBackButton();
                if (menu.isBackPressed()) {
                    currentState = MAIN_MENU;
                    menu.resetBackPressed(); // Réinitialiser l'état du bouton
                }
                break;

            case ABOUT:
                menu.updateBackButton();
                if (menu.isBackPressed()) {
                    currentState = MAIN_MENU;
                    menu.resetBackPressed(); 
                }
                break;
        }

        sudokuGUI.update();
        BeginDrawing();
        ClearBackground(darkGreen);

        switch (currentState)
        {
            case MAIN_MENU:
                menu.draw();
                break;

            case GAMEPLAY:
                sudokuGUI.draw();
                break;

            case CREDITS:
                menu.drawCredits();
                break;

            case ABOUT:
                menu.drawAbout();
                break;
        }

        sudokuGUI.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
