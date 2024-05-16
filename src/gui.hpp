#ifndef GUI_H
#define GUI_H

#include "grid.hpp"
#include "buttons.hpp"

class GUI {
    private:
        Grid sudokuGrid;
    public:
        GUI();
        void draw();
        void update();
        void fillGrid();
};

#endif  // GUI_H