// creation sudoku grid in terminal

#include <iostream>
#include <vector>
#include <string>
#include "grid.hpp"
using namespace std;


Grid::Grid() {
    cells.resize(SIZE, vector<int>(SIZE, 0));
}

void Grid::drawGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << cells[i][j] << " ";
            if ((j + 1) % 3 == 0 && j < SIZE - 1) {
                cout << "| ";
            }
        }
        std::cout << endl;
        if ((i + 1) % 3 == 0 && i < SIZE - 1) {
            cout << "---------------------" << endl;
        }
    }
}

Grid::CellPosition Grid::getCellPosition(int row, int col) {
    return {row, col};
}

void Grid::setCellValue(int row, int col, int value) {
    cells[row][col] = value;
}

int Grid::getCellValue(int row, int col) {
    return cells[row][col];
}