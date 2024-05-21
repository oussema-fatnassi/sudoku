#include "grid.hpp"
#include "cell.hpp"
#include "algorithms.hpp"
#include <raylib.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
// #include <intrin.h>
#include <cstring>
using namespace std;

Grid::Grid() : selectedCell(nullptr) {                                              // Default constructor
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cells[row][col] = Cell(row, col);
        }
    }
}

Grid::~Grid() {                                                                     // Destructor
}

Cell& Grid::getCell(int row, int col) {                                             // Function to get the cell at the specified row and column
    return cells[row][col];
}

Cell* Grid::getSelectedCell() {                                                     // Function to get the selected cell
    return selectedCell;
}

void Grid::loadGridFromFile(const char* difficulty) {                               // Function to load the Sudoku grid from a file
    const char* easy = "easy";
    const char* medium = "medium";
    const char* hard = "hard";
    if (strcmp(difficulty, easy) == 0) {                                            // strcmp compares two strings
        filename = "assets/easy.txt";
        solutionFilename = "assets/easy_solution.txt";
    }
    else if (strcmp(difficulty, medium) == 0) {
        filename = "assets/medium.txt";
        solutionFilename = "assets/medium_solution.txt";
    }
    else if (strcmp(difficulty, hard) == 0) {
        filename = "assets/hard.txt";
        solutionFilename = "assets/hard_solution.txt";
    }
    else {
        std::cerr << "Error: Invalid difficulty level" << std::endl;
        return;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    allGrids.clear();                                                               // Clear the vector
    vector<int> row(SIZE, 0);
    vector<vector<int>> grid(SIZE, row);
    int gridCount = 0;
    while (file) {                                                                  // Read the grid from the file
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                file >> grid[i][j];
            }
        }
        allGrids.push_back(grid);                                                   // Add the grid to the vector
        gridCount++;
    }
    file.close();

    std::ifstream solution_file(solutionFilename);                                  // Read the solution from the file
    if (!solution_file.is_open()) {
        std::cerr << "Error: Unable to open file " << solutionFilename << std::endl;
        return;
    }
    allSolutions.clear();                                                           // Clear the vector
    gridCount = 0;
    while (solution_file) {                                                         // Read the solution from the file
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                solution_file >> grid[i][j];
            }
        }
        allSolutions.push_back(grid);                                               // Add the solution to the vector
        gridCount++;
    }
    solution_file.close();

    srand(static_cast<unsigned int>(time(0)));                                      // Seed the random number generator

    int randomIndex = rand() % gridCount;
    vector<vector<int>> chosenGrid = allGrids[randomIndex];                         // Choose a random grid
    solution = allSolutions[randomIndex];                                           // Get the solution for the chosen grid
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cells[row][col].value = chosenGrid[row][col];
            if(cells[row][col].value != 0)                                          // Check if the cell is editable
            {
                cells[row][col].isEditable = false; 
            }
            else
            {
                cells[row][col].isEditable = true;
            }
        } 
    }
}

void Grid::checkGrid() {
    if (gridChecked) {
        vector<vector<int>> currentGrid(SIZE, vector<int>(SIZE, 0));                // Get the current grid state
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                currentGrid[row][col] = cells[row][col].value;
            }
        }

        Algorithms solver(currentGrid);                                             // Initialize with the current grid
        solver.solve();                                                             // Solve the grid

        for (int row = 0; row < SIZE; row++) {                                      // Compare the user-input values with the solved grid
            for (int col = 0; col < SIZE; col++) {
                if (cells[row][col].isEditable && cells[row][col].value != 0) {
                    if (cells[row][col].value == solver.getSolution()[row][col]) {
                        cells[row][col].isCorrect = 2;                              // Correct
                    } else {
                        cells[row][col].isCorrect = 1;                              // Incorrect
                    }
                }
            }
        }
        gridChecked = false;
    }
}

bool Grid::checkWinCondition() {                                                    // Function to check the win condition
    vector<vector<int>> currentGrid(SIZE, vector<int>(SIZE, 0));
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            currentGrid[row][col] = cells[row][col].value;
        }
    }

    Algorithms solver(currentGrid);                                                 // Use the solver to check if the current grid matches the solved grid
    solver.solve();
    vector<vector<int>> solvedGrid = solver.getSolution();

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (currentGrid[row][col] != solvedGrid[row][col]) {
                return false;
            }
        }
    }
    return true;
}

void Grid::drawNumber(int row, int col) {                                           // Function to draw the number in the cell
    Cell& cell = getCell(row, col);
    if (cell.value != 0) {
        std::string valueText = std::to_string(cell.value);
        if (cell.isEditable == false) {
            DrawText(valueText.c_str(), col * 60 + 75, row * 60 + 125, 20, BLACK);
        } else {
            if (cell.isCorrect == 2) {
                DrawText(valueText.c_str(), col * 60 + 75, row * 60 + 125, 20, BLUE);
            } else if (cell.isCorrect == 1) {
                DrawText(valueText.c_str(), col * 60 + 75, row * 60 + 125, 20, RED);
            } else {
                DrawText(valueText.c_str(), col * 60 + 75, row * 60 + 125, 20, BLUE);
            }
        }
    }
}

void Grid::drawGrid() {                                                             // Function to draw the Sudoku grid
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            Cell& cell = getCell(row, col);

            Color cellColor = Color{255, 255, 255, 255};                            // Default white color

            if (cell.isSelected) {
                cellColor = Color{0, 173, 181, 255};                                // for selected cell
            } else if (cell.isHighlighted) {
                cellColor = Color{205, 232, 229, 255};                              // for highlighted cells
            }

            DrawRectangle(col * 60 + 50, row * 60 + 100, 60, 60, cellColor);
            drawNumber(row, col);                                                                                       // Draw the number in the cell                                     
            DrawLine(col * 60 + 50, row * 60 + 100, (col + 1) * 60 + 50, row * 60 + 100, Color{0, 0, 0, 255});          // Draw horizontal lines
            DrawLine(col * 60 + 50, (row + 1) * 60 + 100, (col + 1) * 60 + 50, (row + 1) * 60 + 100, Color{0, 0, 0, 255});
            DrawLine(col * 60 + 50, row * 60 + 100, col * 60 + 50, (row + 1) * 60 + 100, Color{0, 0, 0, 255});          // Draw vertical lines
            DrawLine((col + 1) * 60 + 50, row * 60 + 100, (col + 1) * 60 + 50, (row + 1) * 60 + 100, Color{0, 0, 0, 255});
        }
    }
    for (int i = 1; i <= 2; i++) {                                                                                      // Draw thick lines
        DrawRectangle(50, i * 180 + 98, 540, 2, Color{0, 0, 0, 255});                                                   // Horizontal thick lines
        DrawRectangle(i * 180 + 48, 100, 2, 540, Color{0, 0, 0, 255});                                                  // Vertical thick lines
    }
}

void Grid::update() {                                                               // Function to update the grid
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        if (mouseX > 50 && mouseX < 590 && mouseY > 100 && mouseY < 640) {          // Check if the mouse is within the grid
            int row = (mouseY - 100) / 60;
            int col = (mouseX - 50) / 60;
            selectCell(row, col);
            Cell& cell = getCell(row, col);
            if (cell.value != 0) {                                                  // Highlight cells with the same number
                highlightSameNumber(cell.value);
            }
        }
    }

}

void Grid::selectCell(int row, int col) {                                           // Function to select the cell
    if (selectedCell != nullptr) {
        selectedCell->isSelected = false;
    }
    selectedCell = &cells[row][col];
    selectedCell->isSelected = true;

    highlightCells();
    highlightSubgrid();
}

void Grid::highlightCells() {                                                       // Function to highlight the cells
    for (int row = 0; row < 9; row++) {                                             // Resets the highlighted cells
        for (int col = 0; col < 9; col++) {
            cells[row][col].isHighlighted = false;
        }
    }

    if (selectedCell != nullptr) {                                                  // Highlight the row and column of the selected cell
        for (int i = 0; i < 9; i++) {
            cells[selectedCell->row][i].isHighlighted = true;
            cells[i][selectedCell->col].isHighlighted = true;
        }
    }
}

void Grid::highlightSubgrid() {                                                     // Function to highlight the subgrid
    for (int row = 0; row < 9; row += 3) {                                          // Resets the highlighted subgrid
        for (int col = 0; col < 9; col += 3) {
            bool inSubgrid = (selectedCell->row >= row && selectedCell->row < row + 3 &&
                              selectedCell->col >= col && selectedCell->col < col + 3);
            if (inSubgrid) {                                                        // Highlight the subgrid of the selected cell
                for (int i = row; i < row + 3; i++) {
                    for (int j = col; j < col + 3; j++) {
                        cells[i][j].isHighlighted = true;
                    }
                }
                return;                                                             // Subgrid found, no need to check others
            }
        }
    }
}

void Grid::highlightSameNumber(int value) {                                         // Function to highlight cells with the same number
    for (int row = 0; row < 9; row++) {                                             // Resets the highlighted cells
        for (int col = 0; col < 9; col++) {
            cells[row][col].isHighlighted = false;
        }
    }

    for (int row = 0; row < 9; row++) {                                             // Highlight cells with the same number
        for (int col = 0; col < 9; col++) {
            if (cells[row][col].value == value) {
                cells[row][col].isHighlighted = true;
            }
        }
    }
}

void Grid::setCellValue(int value) {                                                // Function to set the cell value
    if (selectedCell != nullptr ) {
        selectedCell->setValue(value);
        selectedCell-> value = value;
        selectedCell->isCorrect = 0;
    }
}

vector<vector<int>> Grid::getCurrentGrid() {                                        // Function to get the current grid
    vector<vector<int>> currentGrid;
    for (int row = 0; row < SIZE; row++) {
        vector<int> currentRow;
        for (int col = 0; col < SIZE; col++) {
            if (!cells[row][col].isEditable) {
                currentRow.push_back(cells[row][col].value);
            } else {
                currentRow.push_back(0); 
            }
        }
        currentGrid.push_back(currentRow);
    }
    return currentGrid;
}
void Grid::clearGrid() {                                                            // Function to clear the grid
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cells[row][col].value = 0;
        }
    }
}
