
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include "grid.hpp"

// Define the size of the Sudoku grid
constexpr int SIZE = 9;

class Algorithms {
public:
    Algorithms(); 

    void solveGrid(Grid& grid);
    static void solveSudoku(vector<vector<int>>& board);
    // Constructor to initialize the class with a given board
    Algorithms(const std::vector<std::vector<int>>& board);

    // Constructor to generate a Sudoku puzzle with a specified number of unknowns
    Algorithms(int maxUnknowns);

    // Method to get the current grid
    std::vector<std::vector<int>> getGrid();

    // Method to get the solution of the current grid
    std::vector<std::vector<int>> getSolution();

    // Method to solve the current grid
    void solve();

    // Method to check if the current grid has a unique solution
    bool isUnique();

private:
    // Method to check if a number can be safely placed in a cell
    bool isSafe(int row, int col, int num);
    static bool solve(vector<vector<int>>& board);
    static bool isValidNumber(vector<vector<int>>& board, int row, int col, int num);

    // Backtracking method to solve the Sudoku puzzle
    bool backtrack(int row, int col);

    // Method to count the number of solutions of the current grid
    void countSolutions(int row, int col);

    // Method to generate a fully solved Sudoku grid
    void generateFullGrid();

    // Number of solutions found for the current grid
    int solutions;

    // The current Sudoku grid
    std::vector<std::vector<int>> grid;

    // The solution of the current grid
    std::vector<std::vector<int>> solution;
};

#endif // ALGORITHMS_HPP
