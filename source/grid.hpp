#ifndef GRID_H
#define GRID_H
#include <vector>

class Grid {
public:
    struct CellPosition {
        int row;
        int col;
    };

    static const int SIZE = 9;

    std::vector<std::vector<int> > cells;

    Grid();
    void drawGrid();
    void loadGridFromFile(const char* filename);
    CellPosition getCellPosition(int row, int col);

    void setCellValue(int row, int col, int value);

    int getCellValue(int row, int col);
};

#endif  // GRID_H