#ifndef BUTTONS_H
#define BUTTONS_H
#include "raylib.h"
#include "grid.hpp"

class Button {
    private:
        float x;
        float y;
        float width;
        float height;
        Color color;
        string text;
        Grid* grid;
    public:
        int number ;
        Button()=default;
        Button(float x, float y, float width, float height, Color color, const char* text, Grid* grid=nullptr);
        void draw();
        void buttonHover();
        void changeCellValue();
        void eraseCellValue();
};
#endif  // BUTTONS_H
