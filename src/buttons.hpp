#ifndef BUTTONS_H
#define BUTTONS_H
#include "raylib.h"

class Button {
    private:
        float x;
        float y;
        float width;
        float height;
        Color color;
        const char* text;
    public:
        Button(float x, float y, float width, float height, Color color, const char* text);
        void draw();
        void buttonHover();
        static void drawNumbers();
        void update();
};

#endif  // BUTTONS_H