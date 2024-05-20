#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP 

#include <vector>
#include "grid.hpp"
using namespace std;

class Algorithms {
    public:
        static void solveSudoku(vector<vector<int>>& board);
        void solveGrid(Grid& grid);
    private:
        static bool solve(vector<vector<int>>& board);
        static bool isValidNumber(vector<vector<int>>& board, int row, int col, int num);
};

#endif  // ALGORITHMS_HPP