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
    bool isCorrect;
    bool isEditable;

    Cell();
    void setValue(int value);
    int getValue();
};

#endif  // CELL_H