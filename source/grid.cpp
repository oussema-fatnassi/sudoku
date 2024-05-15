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
    // loadGridFromFile("sudoku_grid.txt");
    int originalRandomIndex;
    gridDrawn = false;
    // removeRandomValues(1);
    copyUnsolvedGrid();
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
    cells = allGrids[randomIndex];
    cout << "Random index: " << randomIndex << endl;
    originalRandomIndex = randomIndex;
    copyUnsolvedGrid();
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
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        cout << "Invalid row or column index." << endl;
        return;
    }
    cells[row][col] = value;
}

int Grid::getCellValue(int row, int col) {
    return cells[row][col];
}

void Grid::chooseDifficulty(){
    cout << "Choose difficulty level:" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    int choice;

    while(true){
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (choice < 1 || choice > 3) {
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            continue;
        }
        break;
    }

    switch (choice) {
        case 1:
            loadGridFromFile("../assets/easy.txt");
            difficulty = 1;
            break;
        case 2:
            loadGridFromFile("../assets/medium.txt");
            difficulty = 2;
            break;
        case 3:
            loadGridFromFile("../assets/hard.txt");
            difficulty = 3;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            return;
    }
    gridDrawn = true;
    drawGrid();
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
    while (true) {
        if (!gridDrawn) {
            cout << "Welcome to Sudoku!" << endl;
            cout << "1. Difficulty" << endl;
            cout << "2. Exit" << endl;
        } else {
            cout << "1. Choose cell value" << endl;
            cout << "2. Check solution" << endl;
            cout << "3. Exit" << endl;
        }
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                if (!gridDrawn) {
                    chooseDifficulty();
                } else {
                    chooseCellValue();
                }
                break;
            case 2:
                if (!gridDrawn) {
                    cout << "See you next time" << endl;
                    exit(0);
                }
                else {
                    checkSolution();
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

void Grid ::loadGridSolutionFromFile(const char* filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }
        allSolutionGrids.clear();
        vector<int> row(SIZE, 0);
        vector<vector<int>> grid(SIZE, row);
        int gridCount = 0;
        while (file) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    file >> grid[i][j];
                }
            }
            allSolutionGrids.push_back(grid);
            gridCount++;
        }
        file.close();
    }

void Grid:: checkSolution() {
    string solutionFilename;
    switch (difficulty) {
        case 1:
            solutionFilename = "../assets/easy_solution.txt";
            break;
        case 2:
            solutionFilename = "../assets/medium_solution.txt";
            break;
        case 3:
            solutionFilename = "../assets/hard_solution.txt";
            break;
    }
    loadGridSolutionFromFile(solutionFilename.c_str());

    vector<vector<int>> solutionGrid;
    if (originalRandomIndex >= 0 && originalRandomIndex < allSolutionGrids.size()) {
        solutionGrid = allSolutionGrids[originalRandomIndex];
    } else {
        cout << "Error: Unable to load solution grid." << endl;
        return;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (this->cells[i][j] != solutionGrid[i][j]) {
                cout << "Incorrect solution" << endl;
                return;
            }
        }
    }
    cout << "Congratulations! You solved the puzzle" << endl;
}