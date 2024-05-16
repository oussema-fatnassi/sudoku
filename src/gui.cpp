#include "gui.hpp"
#include "grid.hpp"
#include "buttons.hpp"
#include <raylib.h>
#include <iostream>

GUI::GUI() {
    sudokuGrid = Grid();
}

void GUI::update() {
    sudokuGrid.update();
}

void GUI::draw() {
    sudokuGrid.update();
    sudokuGrid.drawGrid();
    Button::drawNumbers(&sudokuGrid);
    Button::drawEraseButton(&sudokuGrid);
    Button::drawCheckButton(&sudokuGrid);
}

void GUI::fillGrid(){
    sudokuGrid.loadGridFromFile("assets/easy.txt");
}