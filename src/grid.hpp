#ifndef GRID_H
#define GRID_H

#include "cell.hpp"

class Grid {
    private:
        Cell cells[9][9];
    public:
        Grid();

        Cell& getCell(int row, int col);
        void drawGrid();

};
#endif  // GRID_H