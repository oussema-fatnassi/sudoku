#ifndef GUI_H
#define GUI_H

#include "grid.hpp"
#include "buttons.hpp"
#include "menu.hpp"
#include "stopwatch.hpp"

using namespace std;

class Menu;                                                             // Forward declaration to avoid circular dependency

class GUI {                                                             // Class for the GUI
public:

    GUI();                                                              // Default constructor
    ~GUI();                                                             // Destructor
    void update();
    void drawGame();
    void drawMainMenu();
    void drawCredits();
    void drawDifficultyMenu();
    void drawEndGame();
    void setDifficulty(const std::string& diff);
    void resetTimer();
    void updateTimer();
    void loadGridUsingAlgorithms(const char* difficulty);               // Function to load the Sudoku grid using the Algorithms class

    Font font;

    Texture2D logoTextureMainMenu, logoTextureCredits;
    Image logoImage;
    Button numberButtons[9];
    Button eraseButton, checkButton, solveButton, closeButton;
    Button startButton, leaderboardButton, creditsButton, exitButton;
    Button backButtonLeaderboard, easyButton, mediumButton, hardButton, backButtonDifficulty, backButtonCredits;
    Button newGameButton, mainMenuButton;
    Grid sudokuGrid;
    bool gameEnded = false;
    float endTime;
    Menu* menu;                                                             // Pointer to the menu
    Stopwatch* stopwatch;

private:
    void drawTexts();
    void drawTimer();
    bool timerStarted;
    std::string username, inputUsername, difficulty;
};

#endif  // GUI_H