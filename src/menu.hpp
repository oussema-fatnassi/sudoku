#ifndef MENU_HPP
#define MENU_HPP

#include <raylib.h>
#include "buttons.hpp"

class Menu {
public:
    Menu();
    ~Menu();
    void draw();
    void drawCredits();
    void drawAbout();
    void update();
    void updateBackButton();
    void resetBackPressed();  
    bool isStartPressed() const;
    bool isCreditsPressed() const;
    bool isAboutPressed() const;
    bool isExitPressed() const;
    bool isBackPressed() const;

private:
    Button startButton;
    Button creditsButton;
    Button aboutButton;
    Button exitButton;
    Button backButton;
    bool startPressed;
    bool creditsPressed;
    bool aboutPressed;
    bool exitPressed;
    bool backPressed;
    Texture2D menuBackground;
    Texture2D creditsBackground;
    Texture2D aboutBackground;
};

#endif // MENU_HPP
