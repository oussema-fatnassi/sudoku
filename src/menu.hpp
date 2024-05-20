#ifndef MENU_HPP
#define MENU_HPP

class GUI;

enum GameState {                                        // Enum for the different states of the game
    MAIN_MENU,
    DIFFICULTY_MENU,
    CREDITS_MENU,
    LEADERBOARD_MENU,
    GAMEPLAY_MENU,
    ENDGAME_MENU,
    CLOSE
};


class Menu {
    private:
        GUI* gui;                                       // Pointer to GUI object
        GameState currentState;                         // Current state of the game

    public:
        Menu();                                        // Constructor
        void drawMenu();                               // All the draw functions
        void updateMenu();
        void setGUI(GUI* gui);

        GameState getCurrentState() const;
        void setCurrentState(GameState state);
        ~Menu();                                       // Destructor
};

#endif // MENU_HPP