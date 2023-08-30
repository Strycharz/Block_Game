//
// Created by Wojtek on 27.08.2023.
//

#ifndef GIERKASFML_LEVELCREATOR_H
#define GIERKASFML_LEVELCREATOR_H

#include "SFML/Graphics.hpp"

#include "SFML/Window.hpp"

#include <fstream>
#include <cstring>
#include <dirent.h>

#include "Plansza.h"

int const width = 15;
int const hight = 15;

class LevelCreator {
//    //Vector storing the map
//    vector<vector<char>> map;

    Plansza &obj_b1;

    sf::Text textCreator[6];
    sf::Font font;

public:
    LevelCreator(Plansza & b);

    void active_text();
    sf::Text getText(int i);

    void save_to_file();
    int count_map_file();
};


#endif //GIERKASFML_LEVELCREATOR_H
