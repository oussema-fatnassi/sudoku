#include <iostream>
#include "grid.hpp"
using namespace std;

int main() {
    Grid sudokuGrid;

    sudokuGrid.drawGrid();

    Grid::CellPosition cellPosition = sudokuGrid.getCellPosition(0, 0);

    // cout << "Cell value at position (1, 2): " << sudokuGrid.getCellValue(cellPosition.row, cellPosition.col) << endl;
    return 0;
}