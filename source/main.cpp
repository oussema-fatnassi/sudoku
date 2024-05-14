#include <iostream>
#include "grid.hpp"
using namespace std;

int main() {
    Grid sudokuGrid;
    int row, col, value;
    sudokuGrid.setCellValue(0, 0, 2);
    sudokuGrid.setCellValue(0, 1, 2);
    sudokuGrid.setCellValue(1, 0, 2);

    sudokuGrid.drawGrid();

    Grid::CellPosition cellPosition = sudokuGrid.getCellPosition(0, 0);
    sudokuGrid.chooseCellValue();
    sudokuGrid.chooseCellValue();
    sudokuGrid.chooseCellValue();
    return 0;
}