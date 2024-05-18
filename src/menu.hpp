#ifndef MENU_HPP
#define MENU_HPP

class GUI;


enum GameState {
    MAIN_MENU,
    DIFFICULTY_MENU,
    CREDITS_MENU,
    LEADERBOARD_MENU,
    GAMEPLAY_MENU,
    CLOSE
};


class Menu {
    private:
        GUI* gui;
        GameState currentState;

    public:
        Menu();
        void drawMenu();
        void updateMenu();
        void setGUI(GUI* gui);

        GameState getCurrentState() const;
        void setCurrentState(GameState state);
};

#endif // MENU_HPP