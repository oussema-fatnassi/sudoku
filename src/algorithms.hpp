#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP 

#include <vector>
#include "grid.hpp"
using namespace std;

class Algorithms {
    public:
        static void solveSudoku(vector<vector<int>>& board);
        void printSolvedSudoku(vector<vector<int>>& board);
        void solveGrid(Grid& grid);
        void generateSudoku(vector<vector<int>>& board);
        void fillBoardUniquely(vector<vector<int>>& board);
        bool isUniqueSolution(vector<vector<int>>& board, int row, int col, int num);
        void removeNumbersUniquely(vector<vector<int>>& board);
        void printSudokuGrid(vector<vector<int>>& board);
        bool generateSudokuHelper(vector<vector<int>>& board);
        void removeNumbers(vector<vector<int>>& board, int difficulty);
        bool hasUniqueSolution(vector<vector<int>>& board);
        void printSudokuBoard(const vector<vector<int>>& board);




    private:
        static bool solve(vector<vector<int>>& board);
        static bool isValidNumber(vector<vector<int>>& board, int row, int col, int num);

};

#endif  // ALGORITHMS_HPP