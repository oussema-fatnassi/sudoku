#ifndef CELL_H
#define CELL_H

class Cell {
public:
    struct cellPosition
    {
        int row;
        int col;
    };
    
    int value;
    bool isHighlighted;
    bool isSelected;
    bool isCorrect;
    bool isEditable;
    int selectedRow;
    int selectedCol;

    Cell();
    void setValue(int value);
    int getValue();
    void isCellSelected();
};

#endif  // CELL_H