//
// Created by Wojtek on 27.08.2023.
//

#include "Menu.h"

Menu::Menu() {
    active_text();
}

void Menu::active_text() {
    textMenu[0].setString("Play");
    textMenu[1].setString("Level Creator");
    textMenu[2].setString("Exit");


    if (!font.loadFromFile("../Tekstury/arial.ttf")) //Load font from file
        exit(0);

    //Text: Play
    textMenu[0].setFont(font);
    textMenu[0].setCharacterSize(40);
    textMenu[0].setFillColor(sf::Color::White);
    textMenu[0].setPosition(150,50);

    //Text: Level creator
    textMenu[1].setFont(font);
    textMenu[1].setCharacterSize(40);
    textMenu[1].setFillColor(sf::Color::White);
    textMenu[1].setPosition(75,150);

    //Text: Exit
    textMenu[2].setFont(font);
    textMenu[2].setCharacterSize(40);
    textMenu[2].setFillColor(sf::Color::White);
    textMenu[2].setPosition(150,250);

}

sf::Text Menu::getText(int i) {
    return textMenu[i];
}

