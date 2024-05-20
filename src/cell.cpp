#include <raylib.h>
#include <iostream>
#include <vector>
#include "cell.hpp"

// Default constructor
Cell::Cell() : row(-1), col(-1), value(0), isHighlighted(false), isSelected(false), isCorrect(0), isEditable(false) {} 

// Constructor with parameters
Cell::Cell(int row, int col) : row(row), col(col), value(0), isHighlighted(false), isSelected(false), isCorrect(0), isEditable(false) {}

void Cell::setValue(int value) {        // Getter and setter for value
    if(isEditable){
        this->value = value;
    }
}

int Cell::getValue() {
    return value;
}

Cell::~Cell() {}                        // Destructor