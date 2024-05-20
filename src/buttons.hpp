#ifndef BUTTONS_H
#define BUTTONS_H
#include "raylib.h"
#include "grid.hpp"
#include <string>

class Button {
    private:
        float x;
        float y;
        float width;
        float height;
        Color color;
        string text;
        Grid* grid;
        bool enabled;
        bool gridGenerated = false;
    public:
        int number ;
        Button()=default;
        Button(float x, float y, float width, float height, Color color, const char* text, Grid* grid=nullptr);
        void draw();
        void buttonHover();
        void changeCellValue();
        void eraseCellValue();
        void checkGridFunction();
        void solveGridFunction();
        bool isClicked();
        void disable();
        void enable();
        void generateGridFunction();
};
#endif  // BUTTONS_H
