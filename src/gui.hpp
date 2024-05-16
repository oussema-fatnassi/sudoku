#ifndef GUI_H
#define GUI_H

#include "grid.hpp"
#include "buttons.hpp"

class GUI {
    private:
        Grid sudokuGrid;
        Button newGameButton;
    public:
        GUI();
        void draw();
        void update();
};

#endif  // GUI_H