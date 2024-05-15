#ifndef GRID_H
#define GRID_H
#include <vector>
using namespace std;

class Grid {
public:
    struct CellPosition {
        int row;
        int col;
    };

    static const int SIZE = 9;

    vector<vector<int> > cells;
    vector<vector<int> > unsolvedGrid;

    Grid();
    void drawGrid();
    void removeRandomValues(int numValuesToRemove);
    CellPosition getCellPosition(int row, int col);
    void loadGridFromFile(const char* filename);
    void printUnsolvedGrid();
    void copyUnsolvedGrid();
    void menu();
    void setCellValue(int row, int col, int value);
    int getCellValue(int row, int col);
    void chooseCellValue();
};

#endif  // GRID_H