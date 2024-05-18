#include "gui.hpp"
#include "grid.hpp"
#include "buttons.hpp"
#include <raylib.h>
#include <iostream>
#include <cstdlib>

using namespace std;

GUI::GUI() {
    sudokuGrid = Grid();
    timerStarted = false;
    menu = nullptr;

    for (int i = 0; i < 9; i++) {
        int x = 38 + i * (55 + 8);
        int y = 700;
        string buttonText = to_string(i + 1); // Convert integer to string
        numberButtons[i] = Button(x, y, 55, 55, WHITE, buttonText.c_str(), &sudokuGrid); // Convert string to const char*
        numberButtons[i].number = i + 1;
    }
    eraseButton = Button(90, 820, 140, 80, WHITE, "Erase", &sudokuGrid);
    checkButton = Button(400, 820, 140, 80, WHITE, "Check", &sudokuGrid);
    solveButton = Button(250, 900, 140, 80, WHITE, "Solve", &sudokuGrid);
    closeButton = Button(35, 20, 50, 50, WHITE, "X", &sudokuGrid);

    startButton = Button(170, 200, 300, 120, WHITE, "Start");
    leaderboardButton = Button(170, 370, 300, 120, WHITE, "Leaderboard");
    creditsButton = Button(170, 525, 300, 120, WHITE, "Credits");
    exitButton = Button(170, 680, 300, 120, WHITE, "Exit");
    backButtonLeaderboard = Button(220, 800, 200, 100, WHITE, "Back");
    easyButton = Button(220, 200, 200, 100, WHITE, "Easy");
    mediumButton = Button(220, 350, 200, 100, WHITE, "Medium");
    hardButton = Button(220, 500, 200, 100, WHITE, "Hard");
    backButtonDifficulty = Button(220, 800, 200, 100, WHITE, "Back");
    backButtonCredits = Button(220, 800, 200, 100, WHITE, "Back");

}

void GUI::update() {
    sudokuGrid.update();
    if (menu != nullptr) {
        menu->updateMenu();
    }
    timer();
    if (closeButton.isClicked()) {
        menu->setCurrentState(MAIN_MENU);
    }
}

void GUI::drawGame() {
    backButtonCredits.disable();
    backButtonLeaderboard.disable();
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


     if (!difficulty.empty()) {
        int textWidth = MeasureText(difficulty.c_str(), 40);
        int x = (GetScreenWidth() - textWidth) / 2;
        DrawText(difficulty.c_str(), x, 650, 40, BLACK);
    }

}

// void GUI::fillGrid(){
//     sudokuGrid.loadGridFromFile("");
// }

float GUI::getElapsedTime() {
    return GetTime() - startTimer;
}

void GUI::drawTimer(){
    int minutes = static_cast<int>((GetTime() - startTimer) / 60);
    int seconds = static_cast<int>(fmod((GetTime() - startTimer), 60.0f));
    if (timerStarted) { // Only draw the timer text if the timer has started
        char timerText[10];
        snprintf(timerText, sizeof(timerText), "%02d:%02d", minutes, seconds);
        DrawText(timerText, 500, 30, 40, BLACK);
    } else {
        DrawText("00:00", 10, 20, 20, BLACK);
    }
}

void GUI::timer(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        if (mouseX > 50 && mouseX < 590 && mouseY > 100 && mouseY < 640) {
            if (!timerStarted) {
                startTimer = GetTime(); // Start the timer when the mouse button is clicked in the grid area for the first time
                timerStarted = true;
            }
            // Select the cell based on the mouse position
            int row = (mouseY - 100) / 60;
            int col = (mouseX - 50) / 60;
            sudokuGrid.selectCell(row, col);
        }
    }
}

void GUI::drawMainMenu() {
    if (menu-> getCurrentState() == MAIN_MENU) {
        startButton.draw();
        leaderboardButton.draw();
        creditsButton.draw();
        exitButton.draw();
        startButton.enable();
        leaderboardButton.enable();
        creditsButton.enable();
        exitButton.enable();
        easyButton.disable();
        mediumButton.disable();
        hardButton.disable();
        backButtonLeaderboard.disable();
        backButtonCredits.disable();
    }
}

void GUI::drawLeaderboard() {
    if (menu->getCurrentState() == LEADERBOARD_MENU){
        backButtonLeaderboard.draw();
        startButton.disable();
        exitButton.disable();
        creditsButton.disable();
        easyButton.disable();
        mediumButton.disable();
        hardButton.disable();
        leaderboardButton.disable();
        backButtonLeaderboard.enable();
    }
}

void GUI::drawCredits() {
    if (menu->getCurrentState() == CREDITS_MENU){
        backButtonCredits.draw();
        exitButton.disable();
        startButton.disable();
        leaderboardButton.disable();
        easyButton.disable();
        mediumButton.disable();
        hardButton.disable();
        creditsButton.disable();
        backButtonCredits.enable();
    }
}

void GUI::drawDifficultyMenu() {
    if (menu->getCurrentState() == DIFFICULTY_MENU){
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
        leaderboardButton.disable();
        drawInputTextBox();
    }
}

void GUI::setDifficulty(const string& diff) {
    difficulty = diff;
}

void GUI::drawInputTextBox(){
        // Input box for username
        int textBoxWidth = 400;
        int textBoxHeight = 40;
        int textBoxX = (GetScreenWidth() - textBoxWidth) / 2;
        int textBoxY = 100;
        DrawRectangle(textBoxX, textBoxY, textBoxWidth, textBoxHeight, LIGHTGRAY);
        DrawText(username.c_str(), textBoxX + 5, textBoxY + 5, 20, BLACK);

        // Get input from user
        int key = GetCharPressed();
        if (key > 0 && key != 127) {
            username += (char)key;
        }
        if (IsKeyPressed(KEY_BACKSPACE) && username.size() > 0) {
            username.pop_back();
        }
}
