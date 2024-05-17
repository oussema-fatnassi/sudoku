#include "buttons.hpp"
#include <raylib.h>
#include <cstdio>
#include "grid.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include "algorithms.hpp"

Button::Button(float x, float y, float width, float height, Color color, const char* text, Grid* grid) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
    this->text = text;
    this->grid = grid;
}

void Button::draw() {
    buttonHover();
    DrawRectangle(x, y, width, height, color);
    const char* buttonText = text.c_str(); // Convert std::string to const char*
    int textWidth = MeasureText(buttonText, 20);
    int textHeight = 20;
    int textSizeX = (width - textWidth) / 2;
    int textSizeY = (height - textHeight) / 2;
    DrawText(buttonText, x + textSizeX, y + textSizeY, 20, BLACK);
}

void Button::buttonHover() {
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height})) {
        color = {205, 232, 229, 255}; // Change the background color
    } else {
        color = WHITE; // Reset the background color
    }
}

void Button::changeCellValue() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height})) {
        if (grid->getSelectedCell() != nullptr && grid->getSelectedCell()->isEditable==true) {
            grid->setCellValue(number);
        }
        std::cout << "Button number: " << number << std::endl;
    }
}

void Button::eraseCellValue(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height})) {
        if (grid->getSelectedCell() != nullptr && grid->getSelectedCell()->isEditable==true) {
            grid->setCellValue(0);
        }
    }
}

void Button::checkGridFunction(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height})) {
        grid->gridChecked = true;
        grid->checkGrid();
        cout << "Checking grid..." << endl;
    }
}

void Button::solveGridFunction(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height})) {
        cout << "Solving grid..." << endl;
        Algorithms algo;
        algo.solveGrid(*grid);
    }
}