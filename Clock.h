//
// Created by Wojtek on 28.08.2023.
//

#ifndef GIERKASFML_CLOCK_H
#define GIERKASFML_CLOCK_H



#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <SFML/System.hpp>

class Clock {
    sf::Clock clock;
    sf::Text clockText;
    sf::Font font;
public:
    Clock();

    void active_text();
    sf::Text getText();

    void setText(std::string t);

    void reset();
    float getElapsedTime();

};


#endif //GIERKASFML_CLOCK_H
