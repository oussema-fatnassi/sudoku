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

Algorithms::Algorithms() : solutions(0), grid(SIZE, std::vector<int>(SIZE, 0)), solution(SIZE, std::vector<int>(SIZE, 0)) {}

void Algorithms:: solveSudoku(vector<vector<int>>& board) {                                     // Function to solve the Sudoku puzzle and print the solution
    if (solve(board)) {
        for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
        cout << "Sudoku solved successfully!" << endl;
    } else {
        cout << "No solution exists for the given Sudoku." << endl;
    }
}

bool Algorithms::isValidNumber(vector<vector<int>>& board, int row, int col, int num) {         // Function to check if the number is valid for the current cell
    // Check if the number is not already in the current row, column and 3x3 subgrid
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num || board[x][col] == num ||
            board[row - row % 3 + x / 3][col - col % 3 + x % 3] == num) {
            return false;
        }
    }
    return true;
}

bool Algorithms::solve(vector<vector<int>>& board) {                                            // Function to solve the Sudoku puzzle using backtracking
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) { 
                for (int num = 1; num <= 9; num++) {
                    if (isValidNumber(board, row, col, num)) {
                        board[row][col] = num;
                        if (solve(board)) {
                            return true;
                        }
                        board[row][col] = 0;                                                    // Undo and try the next number
                    }
                }
                return false;                                                                   // Trigger backtracking
            }
        }
    }
    return true;                                                                                // Solved
}

void Algorithms::solveGrid(Grid& grid) {                                                        // Function to solve the current Sudoku grid
    vector<vector<int>> board = grid.getCurrentGrid();
    solveSudoku(board);
}


// Constructor to initialize the class with a given board
Algorithms::Algorithms(const std::vector<std::vector<int>>& board) : solutions(0), grid(board),  solution(SIZE, std::vector<int>(SIZE)) {}

// Method to get the current grid
std::vector<std::vector<int>> Algorithms::getGrid() {
    return grid;
}

// Method to check if a number can be safely placed in a cell
bool Algorithms::isSafe(int row, int col, int num) {
    // Check the row and column
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num || grid[i][col] == num) return false;
    }

    // Check the 3x3 sub-grid
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (int i = boxRow; i < boxRow + 3; i++) {
        for (int j = boxCol; j < boxCol + 3; j++) {
            if (grid[i][j] == num) return false;
        }
    }

    return true;
}

// Backtracking method to solve the Sudoku puzzle
bool Algorithms::backtrack(int row, int col) {
    // If we reach the end of the grid, mark the puzzle as solved
    if (row == SIZE - 1 && col == SIZE) {
        solution = grid;
        return true;
    }

    // Move to the next row if we reach the end of the current row
    if (col == SIZE) {
        col = 0;
        row++;
    }

    // Skip filled cells
    if (grid[row][col] > 0) {
        return backtrack(row, col + 1);
    }

    // Try placing numbers 1-9 in the current cell
    std::vector<int> nums {1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(nums.begin(), nums.end(), std::default_random_engine(seed));

    for (int num : nums) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (backtrack(row, col + 1)) return true;
            grid[row][col] = 0; // Undo the move
        }
    }
    return false;
}

// Method to count the number of solutions of the current grid
void Algorithms::countSolutions(int row, int col) {
    // If we reach the end of the grid, increment the solution count
    if (row == SIZE - 1 && col == SIZE) {
        solutions++;
        return;
    }

    // Move to the next row if we reach the end of the current row
    if (col == SIZE) {
        col = 0;
        row++;
    }

    // Skip filled cells
    if (grid[row][col] > 0) {
        countSolutions(row, col + 1);
        return;
    }

    // Try placing numbers 1-9 in the current cell and count solutions
    for (int num = 1; num <= SIZE; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            countSolutions(row, col + 1);
            if (solutions > 1) return;  // Stop early if more than one solution is found
            grid[row][col] = 0; // Undo the move
        }
    }
}

// Method to solve the current grid
void Algorithms::solve() {
    solutions = 0;
    backtrack(0, 0);
}

// Method to check if the current grid has a unique solution
bool Algorithms::isUnique() {
    solutions = 0;
    countSolutions(0, 0);
    return solutions == 1;
}

// Method to generate a fully solved Sudoku grid
void Algorithms::generateFullGrid() {
    grid = std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE, 0));
    backtrack(0, 0);
    solution = grid;
}

// Constructor to generate a Sudoku puzzle with a specified number of unknowns
Algorithms::Algorithms(int maxUnknowns) {
    // Generate a fully solved grid
    generateFullGrid();

    // Create a list of all cell positions
    std::vector<std::tuple<int, int, int>> cells;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cells.emplace_back(i, j, grid[i][j]);
        }
    }

    // Shuffle the cells to randomize the removal process
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cells.begin(), cells.end(), std::default_random_engine(seed));

    int unknowns = 0;
    for (const auto& cell : cells) {
        int row, col, val;
        std::tie(row, col, val) = cell;
        int savedValue = grid[row][col];
        grid[row][col] = 0;

        // Check if the grid still has a unique solution
        Algorithms solver(grid);
        if (!solver.isUnique()) {
            grid[row][col] = savedValue;
        } else {
            unknowns++;
            if (unknowns == maxUnknowns) break;
        }
    }

    // Verify the final grid has a unique solution
    Algorithms solver(grid);
    if (!solver.isUnique()) {
        throw std::runtime_error("Failed to generate a unique solution Sudoku puzzle.");
    }
}

// Method to get the solution of the current grid
std::vector<std::vector<int>> Algorithms::getSolution() {
    return solution;
}
