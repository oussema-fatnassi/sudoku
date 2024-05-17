#include "algorithms.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>
#include "grid.hpp"
using namespace std;

void Algorithms:: solveSudoku(vector<vector<int>>& board) {
    // vector<vector<int>> board = {
    //     {7, 9, 5, 8, 4, 0, 0, 6, 0},
    //     {8, 1, 2, 9, 0, 0, 0, 4, 0},
    //     {6, 0, 0, 0, 7, 2, 8, 0, 9},
    //     {0, 0, 0, 1, 9, 0, 0, 0, 0},
    //     {0, 5, 0, 7, 6, 8, 1, 3, 4},
    //     {1, 0, 6, 3, 2, 0, 0, 0, 8},
    //     {0, 0, 1, 6, 0, 3, 4, 0, 7},
    //     {9, 6, 0, 4, 0, 0, 0, 0, 0},
    //     {4, 7, 0, 0, 0, 0, 0, 5, 0}
    // };
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


    
