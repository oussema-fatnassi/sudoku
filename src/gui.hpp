#ifndef GUI_H
#define GUI_H

#include "grid.hpp"
#include "buttons.hpp"

class GUI {
    private:
    
    public:
        Grid sudokuGrid;
        Button numberButtons[9];
        Button eraseButton;
        Button checkButton;
    public:
        GUI();
        void draw();
        void update();
        void fillGrid();
};

#endif  // GUI_H