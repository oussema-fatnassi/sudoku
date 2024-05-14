// creation sudoku grid in terminal

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "grid.hpp"
using namespace std;


Grid::Grid() {
    cells.resize(SIZE, vector<int>(SIZE, 1));
    loadGridFromFile("sudoku.txt");
}

void Grid::loadGridFromFile(const char* filename) {                                   // Load the grid from the specified file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    int row = 0;
    int col = 0;
    while (file >> cells[row][col]) {
        col++;
        if (col >= SIZE) {
            col = 0;
            row++;
        }
    }
    file.close();
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

void Grid::chooseCellValue() {
    int row, col, value;
    cout << "Enter a row between 1 and 9 : ";
    cin >> row;
    cout << "Enter a column between 1 and 9 : ";
    cin >> col;
    cout << "Enter a value between 1 and 9 : ";
    cin >> value;
    setCellValue(row -1, col -1, value);
    drawGrid();
}