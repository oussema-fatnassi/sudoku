#include "gui.hpp"
#include "grid.hpp"
#include "buttons.hpp"
#include <raylib.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "stopwatch.hpp"
#include <cmath>
#include "algorithms.hpp"
#include "cell.hpp"

using namespace std;

GUI::GUI() {
    sudokuGrid = Grid();                                                            // Initialize the grid
    timerStarted = false;
    gameEnded = false;
    menu = nullptr;                                                                 // Initialize the menu pointer to nullptr

    for (int i = 0; i < 9; i++) {                                                   // Initialize the number buttons
        int x = 38 + i * (55 + 8);
        int y = 700;
        string buttonText = to_string(i + 1);                                       // Convert integer to string
        numberButtons[i] = Button(x, y, 55, 55, WHITE, buttonText.c_str(), &sudokuGrid); // Convert string to const char*
        numberButtons[i].number = i + 1;
    }                                                                               // Initialize the buttons
    eraseButton = Button(90, 820, 140, 50, WHITE, "Erase", &sudokuGrid);
    checkButton = Button(400, 820, 140, 50, WHITE, "Check", &sudokuGrid);
    solveButton = Button(250, 900, 140, 50, WHITE, "Solve", &sudokuGrid);
    closeButton = Button(35, 20, 50, 50, WHITE, "X", &sudokuGrid);

    startButton = Button(220, 600, 200, 50, WHITE, "START");
    creditsButton = Button(220, 660, 200, 50, WHITE, "CREDITS");
    exitButton = Button(220, 720, 200, 50, WHITE, "EXIT");
    backButtonCredits = Button(220, 800, 200, 50, WHITE, "BACK");

    easyButton = Button(220, 400, 200, 50, WHITE, "EASY");
    mediumButton = Button(220, 460, 200, 50, WHITE, "MEDIUM");
    hardButton = Button(220, 520, 200, 50, WHITE, "HARD");
    backButtonDifficulty = Button(220, 700, 200, 50, WHITE,"BACK");

    stopwatch = new Stopwatch();                                                    // Initialize the stopwatch

    logoImage = LoadImage("assets/images/logo.png");                                // Load the logo image
    ImageResize(&logoImage, 400, 400);
    logoTextureMainMenu = LoadTextureFromImage(logoImage);
    
    ImageResize(&logoImage, 200, 200);
    logoTextureCredits = LoadTextureFromImage(logoImage);
    UnloadImage(logoImage);

}

GUI::~GUI() {                                                                       // Destructor
    delete stopwatch;
    UnloadTexture(logoTextureMainMenu);
    UnloadTexture(logoTextureCredits);
}

void GUI::loadGridUsingAlgorithms(const char* difficulty) {                         // Function to load the Sudoku grid using the Algorithms class
    
    Algorithms algorithms;
    int maxUnknowns = 0;
    if (strcmp(difficulty, "EASY") == 0) {
        maxUnknowns = 40;
    } else if (strcmp(difficulty, "MEDIUM") == 0) {
        maxUnknowns = 50;
    } else if (strcmp(difficulty, "HARD") == 0) {
        maxUnknowns = 60;
    }
    algorithms = Algorithms(maxUnknowns);
    vector<vector<int>> grid = algorithms.getGrid();

    for (int row = 0; row < SIZE; row++) {                                                      
        for (int col = 0; col < SIZE; col++) {
            sudokuGrid.cells[row][col].value = grid[row][col];
             if(sudokuGrid.cells[row][col].value != 0)                                          // Check if the cell is editable
            {
                sudokuGrid.cells[row][col].isEditable = false; 
            }
            else
            {
                sudokuGrid.cells[row][col].isEditable = true;
            }
        }
    }
    
}

void GUI::update() {                                                                // Function to update the GUI
    sudokuGrid.update();
    if (menu != nullptr) {
        menu->updateMenu();
    }
    updateTimer();
    if (closeButton.isClicked()) {
        menu->setCurrentState(MAIN_MENU);
        resetTimer();
    }
    if (sudokuGrid.checkWinCondition()) {
        gameEnded = true;
        stopwatch->stop();
        sudokuGrid.clearGrid();
        menu->setCurrentState(ENDGAME_MENU);
        }
    }

void GUI::drawGame() {                                                              // Function to draw the game
    backButtonCredits.disable();
    backButtonDifficulty.disable();
    easyButton.disable();
    mediumButton.disable();
    hardButton.disable();
    sudokuGrid.update();
    sudokuGrid.drawGrid();
    for (int i = 0; i < 9; i++) {
        numberButtons[i].draw();
        numberButtons[i].changeCellValue();
    }
    eraseButton.draw();
    checkButton.draw();
    solveButton.draw();
    closeButton.draw();
    solveButton.solveGridFunction();
    eraseButton.eraseCellValue();
    checkButton.checkGridFunction();
    drawTimer();
    drawTexts();
}

void GUI:: resetTimer() {                                                           // Function to reset the timer
    gameEnded = false;
    stopwatch->reset();
    stopwatch->stop();
}

void GUI::drawTexts() {                                                             // Function to draw the text of the difficulty level
    if (!difficulty.empty()) {
        DrawText(difficulty.c_str(), 150, 60, 30, BLACK);
    }
}

void GUI::drawTimer() {                                                             // Function to draw the timer
    char timerText[10];
    snprintf(timerText, sizeof(timerText), "%02d:%02d", stopwatch->getMinutes(), stopwatch->getSeconds());
    DrawText(timerText, 500, 60, 30, BLACK);
}

void GUI::updateTimer() {                                                           // Function to update the timer
    if (gameEnded) {
        return;                                                                     // Don't update timer if game has ended
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {                                  // Start the timer when the user clicks on the grid
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        if (mouseX > 50 && mouseX < 590 && mouseY > 100 && mouseY < 640) {
            if (!stopwatch->isRunning()) {
                stopwatch->start();
            } else {
                int row = (mouseY - 100) / 60;
                int col = (mouseX - 50) / 60;
                sudokuGrid.selectCell(row, col);
            }
        }
    }
    stopwatch->update();                                                            
}

void GUI::drawEndGame() {                                                           // Function to draw the end game screen
    gameEnded = true;
    Color colorRectangle = {205, 232, 229, 255};
    DrawRectangle(85, 160, 470, 400, colorRectangle);
    int victoryTextWidth = MeasureText("You win!", 40);
    int xVictoryText = (GetScreenWidth() - victoryTextWidth) / 2;

    DrawText("You win!", xVictoryText, 200, 40, BLACK);
    DrawText("Congratulations! You finished", 150, 350, 20, BLACK);
    DrawText("the game in ", 150, 380, 20, BLACK);

    char timerText[10];
    snprintf(timerText, sizeof(timerText), "%02d:%02d", stopwatch->getMinutes()-2, stopwatch->getSeconds());
    DrawText(timerText, 280, 380, 20, BLACK);

    newGameButton = Button(155, 450, 150, 60, WHITE, "New Game");
    mainMenuButton = Button(335, 450, 150, 60, WHITE, "Main Menu");
    newGameButton.draw();
    mainMenuButton.draw();
    newGameButton.enable();
    mainMenuButton.enable();
}

void GUI::drawMainMenu() {                                                          // Function to draw the main menu
    if (menu->getCurrentState() == MAIN_MENU) {
        DrawTexture(logoTextureMainMenu, 125, 50, WHITE);

        startButton.draw();
        creditsButton.draw();
        exitButton.draw();
        startButton.enable();
        creditsButton.enable();
        exitButton.enable();
        easyButton.disable();
        mediumButton.disable();
        hardButton.disable();
        backButtonCredits.disable();
        newGameButton.disable();
        mainMenuButton.disable();
    }
}

void GUI::drawCredits() {                                                           // Function to draw the credits
    if (menu->getCurrentState() == CREDITS_MENU) {
        DrawTexture(logoTextureCredits, 225, 50, WHITE);

        DrawText("Created by:", 220, 300, 20, BLACK);
        DrawText("Baptiste APPRIOU", 50, 350, 20, BLACK);
        DrawText("Oussema FATNASSI", 50, 400, 20, BLACK);
        DrawText("Ali Abakar ISSA", 50, 450, 20, BLACK);

        backButtonCredits.draw();
        exitButton.disable();
        startButton.disable();
        easyButton.disable();
        mediumButton.disable();
        hardButton.disable();
        creditsButton.disable();
        backButtonCredits.enable();
        newGameButton.disable();
        mainMenuButton.disable();
    }
}

void GUI::drawDifficultyMenu() {                                                    // Function to draw the difficulty menu
    if (menu->getCurrentState() == DIFFICULTY_MENU) {
        DrawText("Sudoku is a logic-based, combinatorial number-placement puzzle.", 100, 100, 15, BLACK);
        DrawText("The objective is to fill a 9x9 grid with digits so that each column,", 100, 125, 15, BLACK);
        DrawText("each row, and each of the nine 3x3 subgrids that compose the grid", 90, 150, 15, BLACK);
        DrawText("contain all of the digits from 1 to 9 without ripetitions.", 140, 175, 15, BLACK);
        DrawText("Choose your difficulty level:", 170, 250, 20, BLACK);

        easyButton.draw();
        mediumButton.draw();
        hardButton.draw();
        easyButton.enable();
        mediumButton.enable();
        hardButton.enable();
        backButtonDifficulty.draw();
        startButton.disable();
        exitButton.disable();
        creditsButton.disable();
        backButtonDifficulty.enable();
        newGameButton.disable();
        mainMenuButton.disable();
    }
}

void GUI::setDifficulty(const string& diff) {                                       // Function to set the difficulty level
    difficulty = diff;
}