#ifndef GRID_H
#define GRID_H

#include "cell.hpp"

class Grid {
    public:
        Cell cells[9][9];
        Grid();

        Cell& getCell(int row, int col);
        void drawGrid();
};
#endif  // GRID_H