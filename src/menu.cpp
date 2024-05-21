#include "menu.hpp"
#include "gui.hpp"

Menu::Menu() {                                              // Constructor
    currentState = MAIN_MENU;
    gui = nullptr;
}

void Menu::setGUI(GUI* gui) {                               // Set GUI
    this->gui = gui;
}

void Menu::drawMenu() {                                     // Draw menu
    if(gui == nullptr) {
        return;
    }

    switch (currentState) {                                 // Switch case for different states
        case MAIN_MENU:
            gui->drawMainMenu();
            break;
        case CREDITS_MENU:
            gui->drawCredits();
            break;
        case DIFFICULTY_MENU:
            gui->drawDifficultyMenu();
            break;
        case GAMEPLAY_MENU:
            gui->drawGame();
            break;
        case ENDGAME_MENU:
            gui->drawEndGame();
            break;
        case CLOSE:
            CloseWindow();
        default:
            break;
    }
}

void Menu::updateMenu() {                                   // Update menu
    if(gui == nullptr) {                                    // Check if GUI is null
        return;
    }
    if (gui->startButton.isClicked()) {                     // Check what button is clicked and change state accordingly
        currentState = DIFFICULTY_MENU;
    }
    else if (gui->creditsButton.isClicked()) {
        currentState = CREDITS_MENU;
    }

    else if (gui->exitButton.isClicked()) {
        currentState = CLOSE;
    }
    else if (gui->backButtonCredits.isClicked()) {
        currentState = MAIN_MENU;
    }
    else if (gui->backButtonDifficulty.isClicked()) {
        currentState = MAIN_MENU;
    }
    else if (gui->easyButton.isClicked()) {
        currentState = GAMEPLAY_MENU;
        gui->loadGridUsingAlgorithms("EASY");
        gui->setDifficulty("EASY");
        gui->resetTimer();
    }
    else if (gui->mediumButton.isClicked()) {
        currentState = GAMEPLAY_MENU;
        gui->loadGridUsingAlgorithms("MEDIUM");
        gui->setDifficulty("MEDIUM");
        gui->resetTimer();
    }
    else if (gui->hardButton.isClicked()) {
        currentState = GAMEPLAY_MENU;
        gui->loadGridUsingAlgorithms("HARD");
        gui->setDifficulty("HARD");
        gui->resetTimer();
    }
    else if (gui->newGameButton.isClicked()) {
        gui->gameEnded = true;
        gui->resetTimer();
        currentState = DIFFICULTY_MENU;
    }
    else if (gui->mainMenuButton.isClicked()) {
        gui->gameEnded = true;
        gui->resetTimer();
        currentState = MAIN_MENU;
    }
}

void Menu::setCurrentState(GameState state) {               // Set current state according to the state passed
    currentState = state;
}

GameState Menu::getCurrentState() const {                   // Get current state
    return currentState;
}

Menu::~Menu() {                                             // Destructor
    gui = nullptr;
}