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
        const char* text;
        Grid* grid;
        int number;
    public:
        Button(float x, float y, float width, float height, Color color, const char* text, Grid* grid=nullptr);
        void draw();
        void buttonHover();
        static void drawNumbers( Grid* grid=nullptr);
        void buttonClicked();
        void update();
};

#endif  // BUTTONS_H