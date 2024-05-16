#include "cell.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>

Cell::Cell() : row(-1), col(-1), value(0), isHighlighted(false), isSelected(false), isCorrect(false), isEditable(false) {}

Cell::Cell(int row, int col) : row(row), col(col), value(0), isHighlighted(false), isSelected(false), isCorrect(false), isEditable(false) {}

void Cell::setValue(int value) {
    if(isEditable){
        this->value = value;
    }
}

int Cell::getValue() {
    return value;
}
