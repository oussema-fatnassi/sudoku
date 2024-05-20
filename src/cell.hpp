#ifndef CELL_H
#define CELL_H

class Cell {
public:
    int row;                        // Row and column of the cell
    int col;
    
    int value;                      // All the properties of the cell
    bool isHighlighted;
    bool isSelected;
    int isCorrect;
    bool isEditable;
    int selectedRow;
    int selectedCol;

    Cell();                         // Default constructor
    Cell(int row, int col);         // Constructor with parameters
    void setValue(int value);       // Getter and setter for value
    int getValue();
    ~Cell();                        // Destructor
};

#endif  // CELL_H