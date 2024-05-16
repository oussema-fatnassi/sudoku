#include "grid.hpp"
#include "cell.hpp"
#include <raylib.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

Grid::Grid() : selectedCell(nullptr) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cells[row][col] = Cell(row, col);
        }
    }
}

Cell& Grid::getCell(int row, int col) {
    return cells[row][col];
}

void Grid::loadGridFromFile(const char* filename) { 
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    allGrids.clear();
    vector<int> row(SIZE, 0);
    vector<vector<int>> grid(SIZE, row);
    int gridCount = 0;
    while (file) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                file >> grid[i][j];
            }
        }
        allGrids.push_back(grid);
        gridCount++;
    }
    file.close();

    srand(static_cast<unsigned int>(time(0)));

    int randomIndex = rand() % gridCount;
    vector<vector<int>> chosenGrid = allGrids[randomIndex];
    cout << "Random index: " << randomIndex << endl;

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cells[row][col].value = chosenGrid[row][col];
        }
    }
}

void Grid::drawNumber(int row, int col) {
    Cell& cell = getCell(row, col);
    if (cell.value != 0) {
        std::string valueText = std::to_string(cell.value);
        DrawText(valueText.c_str(), col * 60 + 75, row * 60 + 125, 20, BLACK);
    }
}

void Grid::drawGrid() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            Cell& cell = getCell(row, col);

            Color cellColor = Color{255, 255, 255, 255}; // Default white color

            if (cell.isSelected) {
                cellColor = Color{0, 173, 181, 255}; // for selected cell
            } else if (cell.isHighlighted) {
                cellColor = Color{205, 232, 229, 255}; // for highlighted cells
            }

            DrawRectangle(col * 60 + 50, row * 60 + 100, 60, 60, cellColor);

            // Draw the cell value if it is non-zero
            drawNumber(row, col);

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

    highlightCells();
    highlightSubgrid();
}

void Grid::highlightCells() {
    // Reset all cell highlights
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cells[row][col].isHighlighted = false;
        }
    }

    if (selectedCell != nullptr) {
        // Highlight the row and column of the selected cell
        for (int i = 0; i < 9; i++) {
            cells[selectedCell->row][i].isHighlighted = true;
            cells[i][selectedCell->col].isHighlighted = true;
        }
    }
}

void Grid::highlightSubgrid() {
    // Reset subgrid highlights
    for (int row = 0; row < 9; row += 3) {
        for (int col = 0; col < 9; col += 3) {
            bool inSubgrid = (selectedCell->row >= row && selectedCell->row < row + 3 &&
                              selectedCell->col >= col && selectedCell->col < col + 3);
            if (inSubgrid) {
                for (int i = row; i < row + 3; i++) {
                    for (int j = col; j < col + 3; j++) {
                        cells[i][j].isHighlighted = true;
                    }
                }
                return; // Subgrid found, no need to check others
            }
        }
    }
}
