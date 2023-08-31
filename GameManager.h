//
// Created by Wojtek on 31.08.2023.
//

#ifndef GIERKASFML_GAMEMANAGER_H
#define GIERKASFML_GAMEMANAGER_H

#include "Board.h"

class GameManager {
    const int width = 15;
    const int height = 15;

    int gameStatus;

    int poziom;

    Board &obj_board;

public:
    GameManager(Board & p);

    int getGameStatus();
    void setGameStatus(int gs);
    bool check_win();

    int getPoziom();
    void setPoziom(int lvl);

    void level_up();
    void level_down();
};


#endif //GIERKASFML_GAMEMANAGER_H
