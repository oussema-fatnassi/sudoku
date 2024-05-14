// creation sudoku grid in terminal
#include <iostream>
#include <vector>
#include <string>
#include "grid.hpp"
#include <fstream>
using namespace std;

Grid::Grid() {
    cells.resize(SIZE, vector<int>(SIZE, 1));
    loadGridFromFile("sudoku_grid.txt");
    removeRandomValues(40);
}

void Grid::loadGridFromFile(const char* filename) { 
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    vector<vector<vector<int>>> allGrids;
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
    cells = allGrids[randomIndex];
}

void Grid::removeRandomValues(int numValuesToRemove) {
    for (int i = 0; i < numValuesToRemove; i++) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        cells[row][col] = 0;
    }
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