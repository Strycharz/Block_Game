//
// Created by Wojtek on 31.08.2023.
//

#include "GameManager.h"

enum STATUS {
    PLAY = 1,
    LEVELCREATOR,
    EXIT,
    MENU
};

GameManager::GameManager(Board & p): obj_board(p){
    poziom = 1;
    gameStatus = MENU;
}


bool GameManager::check_win() {
    int boxCounter = 0;
    int winBoxCounter = 0;

    for(int row = 0; row < height; row++)
        for(int col = 0; col < width; col++){
            if(obj_board.getBox(row,col))
                boxCounter++;
            if(obj_board.get_Field_info(row,col) == 'z')
                winBoxCounter++;
        }

    if(winBoxCounter == boxCounter)
        return true;

    return false;
}

int GameManager::getGameStatus() {
    return gameStatus;
}

void GameManager::setGameStatus(int gs) {
    gameStatus = gs;
}

int GameManager::getPoziom() {
    return poziom;
}

void GameManager::setPoziom(int lvl) {
    poziom = lvl;
}

void GameManager::level_up() {
    poziom++;
}

void GameManager::level_down() {
    poziom--;
}