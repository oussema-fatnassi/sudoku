// #include "menu.hpp"

// Menu::Menu() :
//     startButton(270, 300, 100, 50, DARKGRAY, "Start"),
//     creditsButton(270, 400, 100, 50, DARKGRAY, "Credits"),
//     aboutButton(270, 500, 100, 50, DARKGRAY, "About"),
//     exitButton(270, 600, 100, 50, DARKGRAY, "Exit"),
//     backButton(270, 700, 100, 50, DARKGRAY, "Back"),
//     startPressed(false),
//     creditsPressed(false),
//     aboutPressed(false),
//     exitPressed(false),
//     backPressed(false)
// {
//     menuBackground = LoadTexture("assets/images/background.png"); 
//     creditsBackground = LoadTexture(""); 
//     aboutBackground = LoadTexture(""); 
// }

// Menu::~Menu() {
//     UnloadTexture(menuBackground);
//     UnloadTexture(creditsBackground);
//     UnloadTexture(aboutBackground);
// }

// void Menu::draw() {
//     DrawTexture(menuBackground, 0, 0, WHITE);
//     startButton.draw();
//     creditsButton.draw();
//     aboutButton.draw();
//     exitButton.draw();
// }

// void Menu::drawCredits() {
//     DrawTexture(creditsBackground, 0, 0, WHITE);
//     DrawText("Created by:", 220, 300, 20, WHITE);
//     DrawText("Baptiste APPRIOU", 220, 340, 20, WHITE);
//     DrawText("Oussema FATNASSI", 220, 380, 20, WHITE);
//     DrawText("Abakar Issa ALI", 220, 420, 20, WHITE);
//     backButton.draw();
// }

// void Menu::drawAbout() {
//     DrawTexture(aboutBackground, 0, 0, WHITE);
//     DrawText("About the Game:", 200, 300, 20, WHITE);
//     DrawText("This Sudoku game was developed by:", 200, 340, 20, WHITE);
//     DrawText("GroupeBOA", 200, 380, 20, WHITE);
//     DrawText("Enjoy solving puzzles!", 200, 420, 20, WHITE);
//     backButton.draw();
// }

// // void Menu::update() {
// //     if (startButton.isMouseOver() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
// //         startPressed = true;
// //     }
// //     if (creditsButton.isMouseOver() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
// //         creditsPressed = true;
// //     }
// //     if (aboutButton.isMouseOver() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
// //         aboutPressed = true;
// //     }
// //     if (exitButton.isMouseOver() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
// //         exitPressed = true;
// //     }
// // }

// // void Menu::updateBackButton() {
// //     if (backButton.isMouseOver() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
// //         backPressed = true;
// //     }
// // }

// void Menu::resetBackPressed() {
//     backPressed = false;
// }

// bool Menu::isStartPressed() const {
//     return startPressed;
// }

// bool Menu::isCreditsPressed() const {
//     return creditsPressed;
// }

// bool Menu::isAboutPressed() const {
//     return aboutPressed;
// }

// bool Menu::isExitPressed() const {
//     return exitPressed;
// }

// bool Menu::isBackPressed() const {
//     return backPressed;
// }
