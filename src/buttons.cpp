#include "buttons.hpp"
#include <raylib.h>
#include <cstdio>
#include "grid.hpp"
#include <cstdlib>
#include <iostream>

Button::Button(float x, float y, float width, float height, Color color, const char* text, Grid* grid) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
    this->text = text;
    this->grid = grid;
    this->number = atoi(text);
}

void Button::draw() {
    buttonHover();
    DrawRectangle(x, y, width, height, color);
    int textWidth = MeasureText(text, 20);
    int textHeight = 20;
    int textSizeX = (width - textWidth) / 2;
    int textSizeY = (height - textHeight) / 2;
    DrawText(text, x + textSizeX, y + textSizeY, 20, BLACK);
}

void Button::buttonHover() {
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height})) {
        color = {205, 232, 229, 255}; // Change the background color
    } else {
        color = WHITE; // Reset the background color
    }
}

void Button::buttonClicked() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height})) {
        if (grid->getSelectedCell() != nullptr) {
            grid->setCellValue(number);
            grid->drawNewCellValue(); // Call this method to draw the new value
        }
        std::cout << "Button number: " << number << std::endl;
    }
}

void Button::drawNumbers(Grid* grid) {
    int number = 1;
    char buffer[10];
    for (int i = 0; i < 9; i++) {
        int x = 38 + i * (55 + 8);
        int y = 700;
        snprintf(buffer, sizeof(buffer), "%d", number);
        Button numberButton(x, y, 55, 55, WHITE, buffer, grid);
        numberButton.draw();
        numberButton.buttonClicked();
        number++;
    }
}
