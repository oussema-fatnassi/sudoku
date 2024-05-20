#include <raylib.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "buttons.hpp"
#include "grid.hpp"
#include "algorithms.hpp"

Button::Button(float x, float y, float width, float height, Color color, const char* text, Grid* grid) {        // Constructor
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
    this->text = text;
    this->grid = grid;
    enabled = true;
}

Button::~Button() {}                                                                                            // Destructor

void Button::draw() {                                                                                           // Function to draw the button
        buttonHover();
        DrawRectangle(x, y, width, height, color);
        const char* buttonText = text.c_str();                                                                  // Convert std::string to const char*
        int textWidth = MeasureText(buttonText, 20);
        int textHeight = 20;
        int textSizeX = (width - textWidth) / 2;
        int textSizeY = (height - textHeight) / 2;
        DrawText(buttonText, x + textSizeX, y + textSizeY, 20, BLACK);
}

void Button::buttonHover() {                                                                                    // Function to change the background color of the button when hovered
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height})) {
        color = {205, 232, 229, 255}; 
    } else {
        color = WHITE; 
    }
}

void Button::changeCellValue() {                                                                                // Function to change the cell value
    if (isClicked()) {
        if (grid->getSelectedCell() != nullptr && grid->getSelectedCell()->isEditable==true) {
            grid->setCellValue(number);
        }
    }
}

void Button::eraseCellValue(){                                                                                  // Function to erase the cell value
    if (isClicked()) {
        if (grid->getSelectedCell() != nullptr && grid->getSelectedCell()->isEditable==true) {
            grid->setCellValue(0);
        }
    }
}

void Button::checkGridFunction(){                                                                               // Function called when the check button is clicked
    if (isClicked()) {
        grid->gridChecked = true;
        grid->checkGrid();
    }
}

void Button::solveGridFunction(){                                                                               // Function called when the solve button is clicked
    if (isClicked()) {
        Algorithms algo;
        algo.solveGrid(*grid);
    }
}

bool Button::isClicked() {                                                                                      // Function to check if the button is clicked
    if (!enabled) {
        return false;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), Rectangle{x, y, width, height})) {
        return true;
    }
    return false;
}

void Button::disable() {                                                                                        // Function to disable the button
    enabled = false;
}

void Button::enable() {                                                                                         // Function to enable the button
    enabled = true;
}