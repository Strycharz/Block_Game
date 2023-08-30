//
// Created by Wojtek on 28.08.2023.
//

#include "Clock.h"

Clock::Clock() {
    clock.restart();
    active_text();
}

void Clock::active_text() {

    if (!font.loadFromFile("../Tekstury/arial.ttf")) //Load font from file
        exit(0);

    //Text: Play
    clockText.setFont(font);
    clockText.setCharacterSize(24);
    clockText.setFillColor(sf::Color::White);
    clockText.setPosition(270,10);

}

void Clock::reset() {
    clock.restart();
}

float Clock::getElapsedTime() {
    return clock.getElapsedTime().asSeconds();
}

sf::Text Clock::getText() {
    return clockText;
}

void Clock::setText(std::string t) {
    clockText.setString(t);
}