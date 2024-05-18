#ifndef GUI_H
#define GUI_H

#include "grid.hpp"
#include "buttons.hpp"
#include "menu.hpp"

using namespace std;

class Menu;

class GUI {   
    private:
        string difficulty;
        string username;
        
    public:
        Grid sudokuGrid;
        Menu* menu;
        Button numberButtons[9];
        Button eraseButton;
        Button checkButton;
        Button solveButton;
        Button closeButton;

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
        // void fillGrid();
        float getElapsedTime();
        void timer();
        void drawTimer();
        void resetTimer();
        void drawMainMenu();
        void drawDifficultyMenu();
        void drawLeaderboard();
        void drawCredits();
        void setDifficulty(const string& difficulty);
        void drawInputTextBox();
};

#endif  // GUI_H