#include "algorithms.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>
#include "grid.hpp"
#include <numeric>
using namespace std;

void Algorithms:: solveSudoku(vector<vector<int>>& board) {
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

void Algorithms::printSolvedSudoku(vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

bool Algorithms::isValidNumber(vector<vector<int>>& board, int row, int col, int num) {
    // Check if the number is not already in the current row, column and 3x3 subgrid
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num || board[x][col] == num ||
            board[row - row % 3 + x / 3][col - col % 3 + x % 3] == num) {
            return false;
        }
    }
    return true;
}

bool Algorithms::solve(vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) { // Empty cell
                for (int num = 1; num <= 9; num++) {
                    if (isValidNumber(board, row, col, num)) {
                        board[row][col] = num;
                        if (solve(board)) {
                            return true;
                        }
                        board[row][col] = 0; // Undo and try the next number
                    }
                }
                return false; // Trigger backtracking
            }
        }
    }
    return true; // Solved
}

void Algorithms::solveGrid(Grid& grid) {
    vector<vector<int>> board = grid.getCurrentGrid();
    solveSudoku(board);


}

void Algorithms::generateSudoku(vector<vector<int>>& board) {
    // Start with an empty board
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = 0;
        }
    }
    // Fill the board using backtracking
    generateSudokuHelper(board);
}

bool Algorithms::generateSudokuHelper(vector<vector<int>>& board) {
    // Find the first empty cell
    int row = -1, col = -1;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1) {
            break;
        }
    }
    // If no empty cell found, Sudoku is filled completely
    if (row == -1) {
        return true;
    }
    // Generate random numbers from 1 to 9
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    random_shuffle(nums.begin(), nums.end());
    // Try each number in the empty cell
    for (int num : nums) {
        if (isValidNumber(board, row, col, num)) {
            board[row][col] = num;
            // Recursively fill the rest of the grid
            if (generateSudokuHelper(board)) {
                return true;
            }
            // Backtrack if the current number doesn't lead to a solution
            board[row][col] = 0;
        }
    }
    // No valid number found for the current cell
    return false;
}

void Algorithms::removeNumbers(vector<vector<int>>& board, int difficulty) {
    // Calculate the total number of cells in the Sudoku grid
    int totalCells = 9 * 9;
    // Calculate the number of cells to remove based on the desired difficulty level
    int cellsToRemove = totalCells * difficulty / 100;
    // Randomly shuffle the cell indices
    vector<int> cellIndices(totalCells);
    iota(cellIndices.begin(), cellIndices.end(), 0); // Fill with 0, 1, 2, ..., totalCells - 1
    random_shuffle(cellIndices.begin(), cellIndices.end());

    // Backup the original board
    vector<vector<int>> originalBoard = board;

    // Remove numbers while ensuring uniqueness of solution
    for (int i = 0; i < cellsToRemove; ++i) {
        // Get the cell indices
        int index = cellIndices[i];
        int row = index / 9;
        int col = index % 9;

        // Temporarily remove the number at this cell
        int removedNumber = board[row][col];
        board[row][col] = 0;

        // Check if the puzzle still has a unique solution
        if (!hasUniqueSolution(board)) {
            // If not, restore the removed number
            board[row][col] = removedNumber;
        }
    }
}

bool Algorithms::hasUniqueSolution(vector<vector<int>>& board) {
    // Create a copy of the board
    vector<vector<int>> tempBoard = board;

    // Use backtracking to solve the puzzle
    return solve(tempBoard);
}

void Algorithms::printSudokuBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}




// void Algorithms::generateSudoku(vector<vector<int>>& board) {
//     // Initialize the board with all zeros
//     for (int i = 0; i < 9; i++) {
//         for (int j = 0; j < 9; j++) {
//             board[i][j] = 0;
//         }
//     }

//     // Fill in the board with random numbers, ensuring uniqueness
//     fillBoardUniquely(board);

//     // Remove some numbers to create a solvable puzzle
//     removeNumbersUniquely(board);
// }

// void Algorithms::fillBoardUniquely(vector<vector<int>>& board) {
//     for (int i = 0; i < 9; i++) {
//         for (int j = 0; j < 9; j++) {
//             int num;
//             do {
//                 num = rand() % 9 + 1; // Generate a random number between 1 and 9
//             } while (!isValidNumber(board, i, j, num) || !isUniqueSolution(board, i, j, num));
//             board[i][j] = num;
//         }
//     }
// }

// bool Algorithms::isUniqueSolution(vector<vector<int>>& board, int row, int col, int num) {
//     // Create a temporary copy of the board
//     vector<vector<int>> tempBoard = board;

//     // Place the number in the cell
//     tempBoard[row][col] = num;

//     // Try to solve the Sudoku puzzle from this point
//     if (!solve(tempBoard)) {
//         return false; // If no solution is found, the number is not unique
//     }

//     // If a solution is found, check if it's unique
//     for (int i = 0; i < 9; i++) {
//         for (int j = 0; j < 9; j++) {
//             if (tempBoard[i][j] != board[i][j]) {
//                 return false; // If any cell has a different value, the solution is not unique
//             }
//         }
//     }

//     return true; // The solution is unique
// }

// void Algorithms::removeNumbersUniquely(vector<vector<int>>& board) {
//     int removedCount = 0;
//     while (removedCount < 40) { // Remove 40 numbers to create a moderate puzzle
//         int row = rand() % 9;
//         int col = rand() % 9;
//         if (board[row][col] != 0 && isUniqueSolution(board, row, col, 0)) {
//             board[row][col] = 0;
//             removedCount++;
//         }
//     }
// }

// void Algorithms::printSudokuGrid(vector<vector<int>>& board) {
//     for (int i = 0; i < 9; i++) {
//         for (int j = 0; j < 9; j++) {
//             cout << board[i][j] << " ";
//         }
//         cout << endl;
//     }
// }