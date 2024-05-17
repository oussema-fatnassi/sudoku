#include "algorithms.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>
#include "grid.hpp"
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
