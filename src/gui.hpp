#ifndef GUI_H
#define GUI_H

#include "grid.hpp"
#include "buttons.hpp"

class GUI {    
    public:
        Grid sudokuGrid;
        Button numberButtons[9];
        Button eraseButton;
        Button checkButton;
        Button solveButton;
        float startTimer;
        bool timerStarted;
        GUI();
        void draw();
        void update();
        void fillGrid();
        float getElapsedTime();
        void timer();
};

#endif  // GUI_H