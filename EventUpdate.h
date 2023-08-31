//
// Created by Wojtek on 31.08.2023.
//

#ifndef GIERKASFML_EVENTUPDATE_H
#define GIERKASFML_EVENTUPDATE_H

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Board.h"
#include "Menu.h"
#include "LevelCreator.h"
#include "Clock.h"
#include "BoardManager.h"
#include "GameManager.h"


class EventUpdate {

    Menu &obj_menu1;

    Board &obj_board1;
    Clock &obj_clock;

    LevelCreator &obj_lvlCr1;

    BoardManager &obj_boardManager;
    GameManager &obj_gameManager1;

    char choice;

public:
    EventUpdate(Menu & m, Board & b, Clock & c, LevelCreator & l, GameManager & gm, BoardManager & bm);

    char check_Input(int move);

    void gameplay_update(sf::Event event, bool &flag);
    void menu_text_update(sf::Event event, sf::RenderWindow &win);
    void level_creator_update(sf::Event event, sf::RenderWindow &win,bool &flag2);
    void clock_text_update();

};


#endif //GIERKASFML_EVENTUPDATE_H
