// creation sudoku grid in terminal
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "grid.hpp"
#include <fstream>
using namespace std;

Grid::Grid() {
    cells.resize(SIZE, vector<int>(SIZE, 1));
    loadGridFromFile("sudoku_grid.txt");
    removeRandomValues(40);
    copyUnsolvedGrid();
    // printUnsolvedGrid();
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


void Grid::printUnsolvedGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << unsolvedGrid[i][j] << " ";
        }
        cout << endl;
    }
}

void Grid::copyUnsolvedGrid() {
    unsolvedGrid = cells;
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

void Grid::chooseCellValue() {
    int row, col, value;
    while (true) {
        cout << "Enter a row between 1 and 9: ";
        if (!(cin >> row)) {
            cout << "Invalid input. Please enter a number between 1 and 9." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (row < 1 || row > 9) {
            cout << "Invalid row. Please enter a row between 1 and 9." << endl;
            continue;
        }
        cout << "Enter a column between 1 and 9: ";
        if (!(cin >> col)) {
            cout << "Invalid input. Please enter a number between 1 and 9." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (col < 1 || col > 9) {
            cout << "Invalid column. Please enter a column between 1 and 9." << endl;
            continue;
        }
        if (unsolvedGrid[row - 1][col - 1] != 0) {
            cout << "You can't change values of default grid, please try again" << endl;
            continue;
        }
        cout << "Enter a value between 1 and 9: ";
        if (!(cin >> value)) {
            cout << "Invalid input. Please enter a number between 1 and 9." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (value < 1 || value > 9) {
            cout << "Invalid value. Please enter a value between 1 and 9." << endl;
            continue;
        }
        break;
    }
    setCellValue(row - 1, col - 1, value);
    drawGrid();
}

void Grid::menu() {
    int choice;
    bool gridDrawn = false;
    while (true) {
        if (!gridDrawn) {
            cout << "Welcome to Sudoku!" << endl;
            cout << "1. Draw grid" << endl;
            cout << "2. Choose cell value" << endl;
            cout << "3. Exit" << endl;
        } else {
            cout << "1. Choose cell value" << endl;
            cout << "2. Exit" << endl;
        }
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                if (!gridDrawn) {
                    drawGrid();
                    gridDrawn = true;
                } else {
                    chooseCellValue();
                }
                break;
            case 2:
                if (!gridDrawn) {
                    chooseCellValue();
                }
                else {
                    cout << "See you next time" << endl;
                    exit(0);
                }
                break;
            case 3:
                cout << "See you next time" << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
        }
    }
}