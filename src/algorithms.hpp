
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include "grid.hpp"

constexpr int SIZE = 9;                                                                                         // Size of the Sudoku grid

class Algorithms {
public:
    Algorithms();                                                                                               // Default constructor                     
    Algorithms(const std::vector<std::vector<int>>& board);                                                     // Constructor to initialize the class with a given board
    Algorithms(int maxUnknowns);                                                                                // Constructor to generate a Sudoku puzzle with a specified number of unknowns
    ~Algorithms();                                                                                              // Destructor

    void solveGrid(Grid& grid);                                                                                 // Function to solve the current Sudoku grid
    static void solveSudoku(vector<vector<int>>& board);                                                        // Function to solve the Sudoku puzzle and print the solution

    std::vector<std::vector<int>> getGrid();                                                                    // Method to get the current grid
    std::vector<std::vector<int>> getSolution();                                                                // Method to get the solution of the current grid

    void solve();                                                                                               // Function to solve the Sudoku puzzle

    bool isUnique();                                                                                            // Function to check if the current grid has a unique solution
    bool isSafe(int row, int col, int num);                                                                     // Method to check if a number can be safely placed in a cell

private:

    bool backtrack(int row, int col);                                                                           // Backtracking method to solve the Sudoku puzzle

    void countSolutions(int row, int col);                                                                      // Function to count the number of solutions of the current grid

    void generateFullGrid();                                                                                    // Function to generate a fully solved Sudoku grid

    int solutions;                                                                                              // Number of solutions found for the current grid

    std::vector<std::vector<int>> grid;                                                                         // The current grid

    std::vector<std::vector<int>> solution;                                                                     // The solution of the current grid
};

#endif // ALGORITHMS_HPP
