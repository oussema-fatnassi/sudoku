#include <iostream>
#include "grid.hpp"
using namespace std;

int main() {
    Grid sudokuGrid;

    sudokuGrid.setCellValue(0, 0, 5);
    sudokuGrid.setCellValue(0, 1, 3);
    sudokuGrid.setCellValue(1, 0, 8);

    sudokuGrid.drawGrid();

    Grid::CellPosition cellPosition = sudokuGrid.getCellPosition(0, 0);

    cout << "Cell value at position (0, 0): " << sudokuGrid.getCellValue(cellPosition.row, cellPosition.col) << endl;
    return 0;
}