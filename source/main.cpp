#include <iostream>
#include "grid.hpp"
using namespace std;

int main() {
    Grid sudokuGrid;

    sudokuGrid.setCellValue(0, 0, 2);
    sudokuGrid.setCellValue(0, 1, 2);
    sudokuGrid.setCellValue(1, 0, 2);

    sudokuGrid.drawGrid();

    Grid::CellPosition cellPosition = sudokuGrid.getCellPosition(0, 0);

    cout << "Cell value at position (0, 0): " << sudokuGrid.getCellValue(cellPosition.row, cellPosition.col) << endl;
    return 0;
}