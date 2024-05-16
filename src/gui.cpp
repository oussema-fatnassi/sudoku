#include "gui.hpp"
#include "grid.hpp"
#include "buttons.hpp"
#include <raylib.h>

GUI::GUI() {
    sudokuGrid = Grid();
}

void GUI::draw() {
    sudokuGrid.update();
    sudokuGrid.drawGrid();
    Button::drawNumbers();
}