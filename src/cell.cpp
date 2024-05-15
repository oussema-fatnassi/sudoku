#include "cell.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>

Cell::Cell() {
    value = 0;
    isHighlighted = false;
    isCorrect = false;
    isEditable = false;
}

void Cell::setValue(int value) {
    if(isEditable){
        this->value = value;
    }
}

int Cell::getValue() {
    return value;
}