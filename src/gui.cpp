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
}

void GUI::update() {
    sudokuGrid.update();
    timer();
}

void GUI::draw() {
    sudokuGrid.update();
    sudokuGrid.drawGrid();
    for (int i = 0; i < 9; i++) {
        numberButtons[i].draw();
        numberButtons[i].changeCellValue();
    }
    eraseButton.draw();
    eraseButton.eraseCellValue();
    checkButton.draw();
    solveButton.draw();
    solveButton.solveGridFunction();

    int minutes = static_cast<int>((GetTime() - startTimer) / 60);
    int seconds = static_cast<int>(fmod((GetTime() - startTimer), 60.0f));
    if (timerStarted) { // Only draw the timer text if the timer has started
        char timerText[10];
        snprintf(timerText, sizeof(timerText), "%02d:%02d", minutes, seconds);
        DrawText(timerText, 10, 20, 20, BLACK);
    } else {
        DrawText("00:00", 10, 20, 20, BLACK);
    }
    checkButton.checkGridFunction();
}

void GUI::fillGrid(){
    sudokuGrid.loadGridFromFile("easy");
}

float GUI::getElapsedTime() {
    return GetTime() - startTimer;
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
