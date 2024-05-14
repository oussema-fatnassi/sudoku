#include <iostream>
#include "grid.hpp"
using namespace std;

int main() {
    Grid sudokuGrid;
    int row, col, value;

    sudokuGrid.drawGrid();

    sudokuGrid.chooseCellValue();
    sudokuGrid.printUnsolvedGrid();

    sudokuGrid.chooseCellValue();
    sudokuGrid.chooseCellValue();
    return 0;
}