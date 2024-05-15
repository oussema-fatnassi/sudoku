#include "grid.hpp"
#include "cell.hpp"
#include <raylib.h>
#include <sstream>

using namespace std;

Grid::Grid() : selectedCell(nullptr){
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cells[row][col] = Cell(row, col);
        }
    }
}

Cell& Grid::getCell(int row, int col) {
    return cells[row][col];
}

void Grid::drawGrid() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            Cell& cell = getCell(row, col);
            Color cellColor = cell.isSelected ? Color{255, 0, 0, 255} : Color{255, 255, 255, 255};
            DrawRectangle(col * 60 + 50, row * 60 + 100, 60, 60, cellColor);

            // Draw horizontal lines
            DrawLine(col * 60 + 50, row * 60 + 100, (col + 1) * 60 + 50, row * 60 + 100, Color{0, 0, 0, 255});
            DrawLine(col * 60 + 50, (row + 1) * 60 + 100, (col + 1) * 60 + 50, (row + 1) * 60 + 100, Color{0, 0, 0, 255});

            // Draw vertical lines
            DrawLine(col * 60 + 50, row * 60 + 100, col * 60 + 50, (row + 1) * 60 + 100, Color{0, 0, 0, 255});
            DrawLine((col + 1) * 60 + 50, row * 60 + 100, (col + 1) * 60 + 50, (row + 1) * 60 + 100, Color{0, 0, 0, 255});
        }
    }
    // Draw thicker lines for the 3x3 subgrid borders
    for (int i = 1; i <= 2; i++) {
        // Horizontal thick lines
        DrawRectangle(50, i * 180 + 98, 540, 2, Color{0, 0, 0, 255});
        // Vertical thick lines
        DrawRectangle(i * 180 + 48, 100, 2, 540, Color{0, 0, 0, 255});
    }
}

void Grid::update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        if (mouseX > 50 && mouseX < 590 && mouseY > 100 && mouseY < 640) {
            int row = (mouseY - 100) / 60;
            int col = (mouseX - 50) / 60;
            selectCell(row, col);
        }
    }
}

void Grid::selectCell(int row, int col) {
    if (selectedCell != nullptr) {
        selectedCell->isSelected = false;
    }
    selectedCell = &cells[row][col];
    selectedCell->isSelected = true;
}