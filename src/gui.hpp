#ifndef GUI_H
#define GUI_H

#include "grid.hpp"
#include "buttons.hpp"
#include "menu.hpp"

using namespace std;

class Menu;

class GUI {
public:
    GUI();
    void update();
    void drawGame();
    void drawMainMenu();
    void drawLeaderboard();
    void drawCredits();
    void drawDifficultyMenu();
    void drawEndGame();
    void setDifficulty(const std::string& diff);
    void resetTimer();
    float getElapsedTime();
    void clearUsername();
    void stopTimer();
    Button numberButtons[9];
    Button eraseButton, checkButton, solveButton, closeButton;
    Button startButton, leaderboardButton, creditsButton, exitButton;
    Button backButtonLeaderboard, easyButton, mediumButton, hardButton, backButtonDifficulty, backButtonCredits;
    Button newGameButton, mainMenuButton;
    Grid sudokuGrid;
    bool gameEnded = false;
    float endTime;
    Menu* menu;

private:
    void drawTexts();
    void drawTimer();
    void timer();
    void drawInputTextBox();



    bool timerStarted;
    float startTimer;
    std::string username, savedUsername, difficulty;
};


#endif  // GUI_H