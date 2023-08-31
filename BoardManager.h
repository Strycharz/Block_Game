//
// Created by Wojtek on 30.08.2023.
//

#ifndef GIERKASFML_BOARDMANAGER_H
#define GIERKASFML_BOARDMANAGER_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Board.h"
#include "GameManager.h"

#include <vector>
#include <array>

class BoardManager {

    int width = 15;
    int hight = 15;
    Board &obj_board1;
    GameManager &obj_gameManager;
    sf::Font font;
    sf::Text text[2];

    std::vector<std::vector<sf::Sprite>> sprites;
    std::array<sf::Texture, 12> textures;


    //Vector storing the map
    vector<vector<char>> map;

public:
    BoardManager(Board & b, GameManager & gm);

    void active_board();
    void active_text();
    void field_update(int row, int col);

    void setText();
    void init_board();
    void load_Map_File();
    void rewrite_Map_To_Board();


    std::vector<std::vector<sf::Sprite>> getSprite();
    sf::Text getText(int i);

};


#endif //GIERKASFML_BOARDMANAGER_H
