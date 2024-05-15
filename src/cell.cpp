#include "cell.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>

// Cell::Cell() {
//     value = 0;
//     isHighlighted = false;
//     isCorrect = false;
//     isEditable = false;
//     isSelected = false;
// }

// void Cell::setValue(int value) {
//     if(isEditable){
//         this->value = value;
//     }
// }

// int Cell::getValue() {
//     return value;
// }

// void Cell::isCellSelected() {
//     int mouseX = GetMouseX();
//     int mouseY = GetMouseY();

//     if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
//         if(mouseX > 50 && mouseX < 590 && mouseY > 100 && mouseY < 640){
//         int row = (mouseY - 100) / 60;
//         int col = (mouseX - 50) / 60;
//         selectedRow = row;
//         selectedCol = col;
//         std::cout << "Row: " << row << " Col: " << col << std::endl;
//         isSelected = true;
//         }
//     }
// }


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
