#ifndef GRID_H
#define GRID_H

#include "cell.hpp"

class Grid {
    private:
        Cell cells[9][9];
        Cell* selectedCell;
    public:
        Grid();

        Cell& getCell(int row, int col);
        void drawGrid();
        void update();
        void selectCell(int row, int col);

};
#endif  // GRID_H