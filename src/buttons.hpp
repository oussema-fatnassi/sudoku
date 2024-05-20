#ifndef BUTTONS_H
#define BUTTONS_H
#include "raylib.h"
#include "grid.hpp"
#include <string>

class Button {                                                                  // Class for buttons
    private:                                                                    // Private members                                               
        float x;
        float y;
        float width;
        float height;
        Color color;
        string text;
        Grid* grid;
        bool enabled;
    public:                                                                     // Public members
        int number;
        Button()=default;                                                       // Default constructor                     
        Button(float x, float y, float width, float height, Color color, const char* text, Grid* grid=nullptr);         // Constructor
        void draw();
        void buttonHover();
        void changeCellValue();
        void eraseCellValue();
        void checkGridFunction();
        void solveGridFunction();
        bool isClicked();
        void disable();
        void enable();
        ~Button();                                                              // Destructor
};
#endif  // BUTTONS_H