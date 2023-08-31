//
// Created by Wojtek on 25.08.2023.
//

#ifndef GIERKASFML_SFMLVIEW_H
#define GIERKASFML_SFMLVIEW_H



#include <iostream>
#include <vector>
#include <array>


#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "windows.h"

#include "Board.h"
#include "Menu.h"
#include "LevelCreator.h"
#include "Clock.h"
#include "BoardManager.h"
#include "EventUpdate.h"
#include "GameManager.h"

using namespace std;
//using namespace sf;

class sfmlView {
    int width;
    int height;

    Menu &obj_menu1;

    Board &obj_board1;
    BoardManager &obj_bm1;
    Clock &obj_clock;

    LevelCreator &obj_lvlCr1;

    EventUpdate &obj_eventUp1;

    GameManager &obj_gameManager;



public:

    sfmlView(Menu & m, Board & b, Clock & c, LevelCreator & l, BoardManager & bm, EventUpdate & ev, GameManager & gm);

    void view();


    void draw_Board(sf::RenderWindow &win);
    void draw_Text_Board(sf::RenderWindow &win);
    void draw_Text_Clock(sf::RenderWindow &win);
    void draw_Text_menu(sf::RenderWindow &win);
    void draw_Text_Creator(sf::RenderWindow &win);




};


#endif //GIERKASFML_SFMLVIEW_H
