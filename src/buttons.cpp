#include "buttons.hpp"
#include <raylib.h>
#include <cstdio>

Button::Button(float x, float y, float width, float height, Color color, const char* text) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
    this->text = text;
}

void Button::draw() {
    DrawRectangle(x, y, width, height, color);
    int textWidth = MeasureText(text, 20);
    int textHeight = 20;
    int textSizeX = (width - textWidth) / 2;
    int textSizeY = (height - textHeight) / 2;
    DrawText(text, x + textSizeX, y + textSizeY, 20, WHITE);
}

bool Button::isMouseOver() {
    return CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height});
}

void Button::drawNumbers() {
    int number = 1;
    char buffer[10]; 
    for (int i = 0; i < 9; i++) {
        int x = 38 + i * (55 + 8); 
        int y = 700; 
        snprintf(buffer, sizeof(buffer), "%d", number);
        Button numberButton(x, y, 55, 55, LIGHTGRAY, buffer);
        numberButton.draw();
        number++;
    }
}