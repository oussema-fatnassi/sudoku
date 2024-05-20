// Creation of a sudoku grid and its functionalities
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <fstream>
#include "grid.hpp"
using namespace std;

Grid::Grid() {                                                                      // Constructor
    cells.resize(SIZE, vector<int>(SIZE, 1));
    int originalRandomIndex;
    gridDrawn = false;
    copyUnsolvedGrid();
}

void Grid::loadGridFromFile(const char* filename) {                                 // Method to load a grid from a file
    std::ifstream file(filename);
    if (!file.is_open()) {                                                          // Check if the file is open
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    allGrids.clear();                                                               // Clear the allGrids vector to store the new grids 
    vector<int> row(SIZE, 0);
    vector<vector<int>> grid(SIZE, row);
    int gridCount = 0;
    while (file) {                                                                  // Read the file and store the grids in allGrids
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                file >> grid[i][j];
            }
        }
        allGrids.push_back(grid);
        gridCount++;
    }
    file.close();

    srand(static_cast<unsigned int>(time(0)));                                      // Seed the random number generator

    int randomIndex = rand() % gridCount;
    cells = allGrids[randomIndex];                                                  // Choose a random grid from allGrids
    originalRandomIndex = randomIndex;
    copyUnsolvedGrid();
}

void Grid::printUnsolvedGrid() {                                                    // Method to print the unsolved grid
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << unsolvedGrid[i][j] << " ";
        }
        cout << endl;
    }
}

void Grid::copyUnsolvedGrid() {                                                     // Method to copy the unsolved grid
    unsolvedGrid = cells;                                                           // Copy the cells to unsolvedGrid to keep memory of the original grid
}

void Grid::drawGrid() {                                                             // Method to draw the grid
    for (int i = 0; i < SIZE; i++) {                                                // Loop through the rows and columns of the grid
        for (int j = 0; j < SIZE; j++) {
            cout << cells[i][j] << " ";
            if ((j + 1) % 3 == 0 && j < SIZE - 1) {                                 // Print the vertical lines
                cout << "| ";
            }
        }
        std::cout << endl;
        if ((i + 1) % 3 == 0 && i < SIZE - 1) {                                     // Print the horizontal lines
            cout << "---------------------" << endl;
        }
    }
}

Grid::CellPosition Grid::getCellPosition(int row, int col) {                        // Method to get the cell position
    return {row, col};
}

void Grid::setCellValue(int row, int col, int value) {                              // Method to set the cell value
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {                         // Check if the row and column indices are valid
        cout << "Invalid row or column index." << endl;
        return;
    }
    cells[row][col] = value;                                                        // Set the cell value
}

int Grid::getCellValue(int row, int col) {                                          // Method to get the cell value
    return cells[row][col];
}

void Grid::chooseDifficulty(){                                                      // Method to choose the difficulty level
    cout << "Choose difficulty level:" << endl;                                     // Display the difficulty levels to the user
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    int choice;

    while(true){                                                                    // Get the difficulty level from the user and check if it is valid
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

    switch (choice) {                                                               // Load the grid based on the difficulty level
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
    drawGrid();                                                                     // Draw the grid
}

void Grid::chooseCellValue() {                                                      // Method to choose the cell's value
    int row, col, value;
    while (true) {
        cout << "Enter a row between 1 and 9: ";                                    // Get the row, column, and value from the user and check if they are valid
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
    setCellValue(row - 1, col - 1, value);                                          // Set the cell value
    drawGrid();                                                                     // Redraw the grid
}

void Grid::menu() {                                                                 // Method to display the menu
    int choice;
    while (true) {
        if (!gridDrawn) {                                                           // Display the menu based on whether the grid is drawn or not
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
        switch (choice) {                                                           // Call the appropriate method based on the choice
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

void Grid ::loadGridSolutionFromFile(const char* filename) {                        // Method to load the solution grid from a file
        std::ifstream file(filename);                                               // Same method as in loadGridFromFile
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

void Grid:: checkSolution() {                                                       // Method to check the solution
    string solutionFilename;
    switch (difficulty) {                                                           // Load the solution based on the difficulty level
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
    if (originalRandomIndex >= 0 && originalRandomIndex < allSolutionGrids.size()) { // Get the solution grid based on the original random index
        solutionGrid = allSolutionGrids[originalRandomIndex];
    } else {
        cout << "Error: Unable to load solution grid." << endl;
        return;
    }

    for (int i = 0; i < SIZE; i++) {                                                // Compare the solution grid with the user grid
        for (int j = 0; j < SIZE; j++) {
            if (this->cells[i][j] != solutionGrid[i][j]) {
                cout << "Incorrect solution" << endl;
                return;
            }
        }
    }
    cout << "Congratulations! You solved the puzzle" << endl;                       // Print the message if the solution is correct
}

Grid::~Grid() {                                                                     // Destructor
}