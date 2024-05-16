#include "gui.hpp"
#include "grid.hpp"
#include "buttons.hpp"
#include <raylib.h>
#include <iostream>
#include <cstdlib>

using namespace std;


GUI::GUI() {
    sudokuGrid = Grid();

    for (int i = 0; i < 9; i++) {
        int x = 38 + i * (55 + 8);
        int y = 700;
        string buttonText = to_string(i + 1); // Convert integer to string
        numberButtons[i] = Button(x, y, 55, 55, WHITE, buttonText.c_str(), &sudokuGrid); // Convert string to const char*
        numberButtons[i].number = i + 1;
    }
    eraseButton = Button(90, 820, 140, 80, WHITE, "Erase", &sudokuGrid);
    checkButton = Button(400, 820, 140, 80, WHITE, "Check", &sudokuGrid);
}

void GUI::update() {
    sudokuGrid.update();
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
}

void GUI::fillGrid(){
    sudokuGrid.loadGridFromFile("easy");
}
