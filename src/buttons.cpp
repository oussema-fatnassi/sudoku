#include "buttons.hpp"
#include <raylib.h>

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
    DrawText(text, x + 10, y + 10, 20, WHITE);
}

bool Button::isMouseOver() {
    return CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height});
}