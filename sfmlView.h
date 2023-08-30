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

#include "Plansza.h"
#include "Menu.h"
#include "LevelCreator.h"
#include "Clock.h"

using namespace std;
//using namespace sf;

class sfmlView {
    int width;
    int hight;
    Plansza &obj_board1;
    Menu obj_menu1;
    LevelCreator &obj_lvlCr1;
    Clock obj_clock;


    vector<vector<sf::Sprite>> sprites;
    array<sf::Texture, 12> textures;

    char choice;

    sf::RectangleShape Tablica[15][15];
    sf::Font font;
    sf::Text text;
    sf::Text text2;

public:

    sfmlView(Plansza & b, LevelCreator & l);

    void widok();



    char check_Input(int move);

    void aktualizacjaPola(int row, int col);

    void gameplay_update(sf::Event event, bool &flag);
    void menu_text_update(sf::Event event, sf::RenderWindow &win);
    void level_creator_update(sf::Event event, sf::RenderWindow &win,bool &flag2);
    void clock_text_update();
    void active_Board();

    void RysujPlansze(sf::RenderWindow &win);
    void draw_Text_Board(sf::RenderWindow &win);
    void draw_Text_menu(sf::RenderWindow &win);
    void draw_Text_Creator(sf::RenderWindow &win);




};


#endif //GIERKASFML_SFMLVIEW_H
