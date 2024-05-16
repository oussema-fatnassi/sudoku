#ifndef CELL_H
#define CELL_H

class Cell {
public:
    int row;
    int col;
    
    int value;
    bool isHighlighted;
    bool isSelected;
    bool isCorrect;
    bool isEditable;
    int selectedRow;
    int selectedCol;

    Cell();
    Cell(int row, int col);
    void setValue(int value);
    int getValue();
};

#endif  // CELL_H