#include "algorithms.hpp"
#include "grid.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <tuple>
#include <stdexcept>

using namespace std;

Algorithms::Algorithms()                                                                        // Default constructor
    : solutions(0),
      grid(SIZE, std::vector<int>(SIZE, 0)),
      solution(SIZE, std::vector<int>(SIZE, 0))
{
}

Algorithms::Algorithms(const std::vector<std::vector<int>>& board)                              // Constructor to initialize the class with a given board
    : solutions(0),
      grid(board),
      solution(SIZE, std::vector<int>(SIZE))
{
}

Algorithms::~Algorithms() {                                                                     // Destructor
}
void Algorithms:: solveSudoku(vector<vector<int>>& board) {                                     // Function to solve the Sudoku puzzle and print the solution
    Algorithms solver(board);                                                                   // Pass the board to initialize the solver
    solver.solve();                                                                             // Call the solve method to solve the Sudoku puzzle
    board = solver.getGrid();
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    
    cout << "Sudoku solved successfully!" << endl;
}

void Algorithms::solveGrid(Grid& grid) {                                                        // Function to solve the current Sudoku grid
    vector<vector<int>> board = grid.getCurrentGrid();
    solveSudoku(board);
}

std::vector<std::vector<int>> Algorithms::getGrid() {                                           // Method to get the current grid
    return grid;
}

bool Algorithms::isSafe(int row, int col, int num) {                                            // Method to check if a number can be safely placed in a cell
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return false;
    for (int i = 0; i < SIZE; i++) {                                                            // Loop through the row and column
        if (grid[row][i] == num || grid[i][col] == num) return false;
    }
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (int i = boxRow; i < boxRow + 3; i++) {                                                 // Loop through the 3x3 sub-grid
        for (int j = boxCol; j < boxCol + 3; j++) {
            if (grid[i][j] == num) return false;
        }
    }
    return true;
}

bool Algorithms::backtrack(int row, int col) {                                                  // Backtracking method to solve the Sudoku puzzle
    if (row == SIZE - 1 && col == SIZE) {                                                       // If we reach the end of the grid, mark the puzzle as solved
        solution = grid;
        return true;
    }

    if (col == SIZE) {                                                                          // If we reach the end of the current row, move to the next row
        col = 0;
        row++;
    }

    if (grid[row][col] > 0) {                                                                   // If the cell is already filled, move to the next cell
        return backtrack(row, col + 1);
    }

    std::vector<int> nums {1, 2, 3, 4, 5, 6, 7, 8, 9};                                          // Shuffle the numbers to randomize the order
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();                // Seed for the random number generator
    std::shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));                   // Shuffle the numbers     

    for (int num : nums) {                                                                      // Try placing numbers 1-9 in the current cell
        if (isSafe(row, col, num)) {                                                            // Check if the number can be placed in the cell
            grid[row][col] = num;
            if (backtrack(row, col + 1)) return true;                                           // Recursively call the backtrack method
            grid[row][col] = 0;                                                                 // Undo the move
        }
    }
    return false;
}

void Algorithms::countSolutions(int row, int col) {                                             // Function to count the number of solutions of the current grid
    if (row == SIZE - 1 && col == SIZE) {                                                       // If we reach the end of the grid, increment the solution count
        solutions++;
        return;
    }

    if (col == SIZE) {                                                                          // If we reach the end of the current row, move to the next row
        col = 0;
        row++;
    }

    if (grid[row][col] > 0) {                                                                   // If the cell is already filled, move to the next cell
        countSolutions(row, col + 1);
        return;
    }

    for (int num = 1; num <= SIZE; num++) {                                                     // Try placing numbers 1-9 in the current cell
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            countSolutions(row, col + 1);
            if (solutions > 1) return;                                                          // Stop early if more than one solution is found
            grid[row][col] = 0;                                                                 // Undo the move
        }
    }
}

void Algorithms::solve() {                                                                      // Function to solve the Sudoku puzzle
    solutions = 0;
    backtrack(0, 0);
}

bool Algorithms::isUnique() {                                                                   // Function to check if the current grid has a unique solution
    solutions = 0;
    countSolutions(0, 0);
    return solutions == 1;
}

void Algorithms::generateFullGrid() {                                                           // Function to generate a fully solved Sudoku grid
    grid = std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE, 0));
    backtrack(0, 0);
    solution = grid;
}

Algorithms::Algorithms(int maxUnknowns) {                                                       // Constructor to generate a Sudoku puzzle with a specified number of unknowns
    generateFullGrid();                                                                         // Generate a fully solved Sudoku grid

    std::vector<std::tuple<int, int, int>> cells;                                               // Tuple to store the row, column, and value of a cell
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cells.emplace_back(i, j, grid[i][j]);
        }
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();                // Seed for the random number generator
    std::shuffle(cells.begin(), cells.end(), std::default_random_engine(seed));

    int unknowns = 0;
    for (const auto& cell : cells) {                                                            // Loop through the cells and set the value to 0
        int row, col, val;
        std::tie(row, col, val) = cell;                                                         // Unpack the tuple
        int savedValue = grid[row][col];
        grid[row][col] = 0;

        Algorithms solver(grid);                                                                // Pass the grid to the solver
        if (!solver.isUnique()) {                                                               // Check if the grid has a unique solution
            grid[row][col] = savedValue;
        } else {
            unknowns++;
            if (unknowns == maxUnknowns) break;
        }
    }

    Algorithms solver(grid);                                                                    // Pass the grid to the solver
    if (!solver.isUnique()) {
        throw std::runtime_error("Failed to generate a unique solution Sudoku puzzle.");
    }
}

std::vector<std::vector<int>> Algorithms::getSolution() {                                       // Method to get the solution of the current grid
    return solution;
}