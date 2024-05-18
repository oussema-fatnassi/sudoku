#include "menu.hpp"
#include "gui.hpp"

Menu::Menu() {
    currentState = MAIN_MENU;
    gui = nullptr;
}

void Menu::setGUI(GUI* gui) {
    this->gui = gui;
}

void Menu::drawMenu() {
    if(gui == nullptr) {
        return;
    }

    switch (currentState) {
        case MAIN_MENU:
            gui->drawMainMenu();
            break;
        case CREDITS_MENU:
            gui->drawCredits();
            break;
        case LEADERBOARD_MENU:
            gui->drawLeaderboard();
            break;
        case DIFFICULTY_MENU:
            gui->drawDifficultyMenu();
            break;
        case GAMEPLAY_MENU:
            gui->drawGame();
            break;
        case CLOSE:
            CloseWindow();
        default:
            break;
    }
}

void Menu::updateMenu() {
    if(gui == nullptr) {
        return;
    }   
    if (gui->startButton.isClicked()) {
        currentState = DIFFICULTY_MENU;
    }
    else if (gui->creditsButton.isClicked()) {
        currentState = CREDITS_MENU;
    }
    else if (gui->leaderboardButton.isClicked()) {
        currentState = LEADERBOARD_MENU;
    }
    else if (gui->exitButton.isClicked()) {
        currentState = CLOSE;
    }
    else if (gui->backButtonCredits.isClicked()) {
        currentState = MAIN_MENU;
    }
    else if (gui->backButtonLeaderboard.isClicked()) {
        currentState = MAIN_MENU;
    }
    else if (gui->backButtonDifficulty.isClicked()) {
        currentState = MAIN_MENU;
    }
    else if (gui->easyButton.isClicked()) {
        currentState = GAMEPLAY_MENU;
    }
    else if (gui->mediumButton.isClicked()) {
        currentState = GAMEPLAY_MENU;
    }
    else if (gui->hardButton.isClicked()) {
        currentState = GAMEPLAY_MENU;
    }
}