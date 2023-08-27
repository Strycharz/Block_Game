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

#include "Plansza.h"



using namespace std;
//using namespace sf;

class sfmlView {
    int width;
    int hight;
    Plansza &obj_board1;

sf::Vector2i playerPosition;

sf::Sprite buttonSprite;
array<sf::Texture,3> buttonTextures;
vector<vector<sf::Sprite>> sprites;
array<sf::Texture, 12> textures;

    sf::RectangleShape Tablica[15][15];
    sf::Font font;
    sf::Text text;
    sf::Text text2;
    sf::Text timerText;
public:

    sfmlView(Plansza & b);

    void widok();



    char check_Input(int move);

    void aktualizacjaPola(int row, int col);

    void aktywuj_Plansze();

    void active_Board();

    void RysujPlansze(sf::RenderWindow &win);
};


#endif //GIERKASFML_SFMLVIEW_H
