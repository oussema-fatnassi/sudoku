#ifndef GUI_H
#define GUI_H

#include "grid.hpp"
#include "buttons.hpp"
#include "menu.hpp"

class Menu;

class GUI {    
    public:
        Grid sudokuGrid;
        Menu* menu;
        Button numberButtons[9];
        Button eraseButton;
        Button checkButton;
        Button solveButton;
        Button startButton;
        Button creditsButton;
        Button leaderboardButton;
        Button exitButton;
        Button backButton;
        Button easyButton;
        Button mediumButton;
        Button hardButton;
        Button backButtonCredits;
        Button backButtonLeaderboard;
        Button backButtonDifficulty;

        float startTimer;
        bool timerStarted;
        GUI();
        void drawGame();
        void update();
        void fillGrid();
        float getElapsedTime();
        void timer();
        void drawMainMenu();
        void drawDifficultyMenu();
        void drawLeaderboard();
        void drawCredits();

};

#endif  // GUI_H