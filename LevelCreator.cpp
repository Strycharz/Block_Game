//
// Created by Wojtek on 27.08.2023.
//

#include "LevelCreator.h"



LevelCreator::LevelCreator(Board & b): obj_b1(b){
   active_text();
}

void LevelCreator::active_text() {
    textCreator[0].setString("Z - WALL");
    textCreator[1].setString("X - BOX");
    textCreator[2].setString("C - PLACE");
    textCreator[3].setString("V - PLAYER");
    textCreator[4].setString("B - EREASE");
    textCreator[5].setString("M - SAVE");


    if (!font.loadFromFile("../Tekstury/arial.ttf")) //Load font from file
        exit(0);

    //Text: Z - WALL
    textCreator[0].setFont(font);
    textCreator[0].setCharacterSize(10);
    textCreator[0].setFillColor(sf::Color::White);
    textCreator[0].setPosition(60,350);

    //Text: X - BOX
    textCreator[1].setFont(font);
    textCreator[1].setCharacterSize(10);
    textCreator[1].setFillColor(sf::Color::White);
    textCreator[1].setPosition(60,370);

    //Text: C - PLACE
    textCreator[2].setFont(font);
    textCreator[2].setCharacterSize(10);
    textCreator[2].setFillColor(sf::Color::White);
    textCreator[2].setPosition(120,350);

    //Text: V - PLAYER
    textCreator[3].setFont(font);
    textCreator[3].setCharacterSize(10);
    textCreator[3].setFillColor(sf::Color::White);
    textCreator[3].setPosition(120,370);

    //Text: B - EREASE
    textCreator[4].setFont(font);
    textCreator[4].setCharacterSize(10);
    textCreator[4].setFillColor(sf::Color::White);
    textCreator[4].setPosition(280,350);

    //Text: M - SAVE
    textCreator[5].setFont(font);
    textCreator[5].setCharacterSize(10);
    textCreator[5].setFillColor(sf::Color::White);
    textCreator[5].setPosition(280,370);

}

sf::Text LevelCreator::getText(int i) {
    return textCreator[i];
}

int LevelCreator::count_map_file() {
    int fileCount = 0;
    std::ifstream file;

    // Open files one by one in the directory
    for (int i = 1; ; ++i) {
        std::string filename =  "../Maps/map" + std::to_string(i) + ".txt";
        file.open(filename);
        if (!file.is_open()) {
            break; // Stop when no more files can be opened
        }

        fileCount++;
        file.close();
    }

    return fileCount + 1;
}

void LevelCreator::save_to_file() {

    std::ofstream plik("../Maps/map" + to_string(count_map_file()) + ".txt", std::ios::out | std::ios::trunc);

    if (!plik.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (obj_b1.getWall(row,col)) {
                plik << "# ";
            } else {
                if (obj_b1.getBox(row,col)) {
                    plik << "X ";
                } else if (obj_b1.getPlayer(row,col)) {
                    plik << "Y ";
                } else if (obj_b1.getPlace(row,col)) {
                    plik << "- ";
                } else {
                    plik << ". ";
                }
            }
        }
        plik << std::endl;
    }

    plik.close();
    std::cout << "The board was successfully saved to the file." << std::endl;
    obj_b1.debug_display();
}