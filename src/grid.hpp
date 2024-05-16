#ifndef GRID_H
#define GRID_H
#include <vector>
using namespace std;
#include "cell.hpp"

class Grid {
    private:
        Cell cells[9][9];
        Cell* selectedCell;
    public:
        Grid();

        static const int SIZE = 9;
        vector<vector<vector<int>>> allGrids;

        Cell& getCell(int row, int col);
        void drawNumber(int row, int col);
        void loadGridFromFile(const char* filename);
        void drawGrid();
        void update();
        void selectCell(int row, int col);
        void highlightCells();
        void highlightSubgrid();
        void setCellValue(int value);
        void drawNewCellValue();
        Cell* getSelectedCell() { return selectedCell; }
};
#endif  // GRID_H