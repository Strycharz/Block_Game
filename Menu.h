//
// Created by Wojtek on 27.08.2023.
//

#ifndef GIERKASFML_MENU_H
#define GIERKASFML_MENU_H

#include "SFML/Graphics.hpp"

#include "SFML/Window.hpp"

#include <vector>


class Menu {

    sf::Text textMenu[3];
    sf::Font font;

    int gameStatus;

public:
    Menu();

    void active_text();

    sf::Text getText(int i);

    int getGameStatus();
    void setGameStatus(int gs);

};


#endif //GIERKASFML_MENU_H
