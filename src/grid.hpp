#ifndef GRID_H
#define GRID_H

#include <vector>
using namespace std;
#include "cell.hpp"

class Grid {                                                                // Class for the Sudoku grid
    private:                                                                // Private members
        Cell cells[9][9];
        Cell* selectedCell;
    public:
        Grid();                                                             // Default constructor
        ~Grid();                                                            // Destructor

        static const int SIZE = 9;                                          //Public variables
        vector<vector<vector<int>>> allGrids;
        vector<vector<vector<int>>> allSolutions;
        vector<vector<int>> solution;
        const char* filename;
        const char* solutionFilename;
        bool gridChecked = false;

        Cell& getCell(int row, int col);                                    // Public functions
        Cell* getSelectedCell();    
        void drawNumber(int row, int col);
        void loadGridFromFile(const char* difficulty);
        void checkGrid();
        bool checkWinCondition();
        void drawGrid();
        void update();
        void selectCell(int row, int col);
        void highlightCells();
        void highlightSubgrid();
        void setCellValue(int value);
        void highlightSameNumber(int value);
        void clearGrid();
        vector<vector<int>> getCurrentGrid();
};
#endif  // GRID_H