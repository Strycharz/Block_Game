#include <iostream>

#include <SFML/Graphics.hpp>


#include "Board.h"
#include "sfmlView.h"
#include "LevelCreator.h"
#include "Menu.h"
#include "Clock.h"
#include "BoardManager.h"
#include "EventUpdate.h"
#include "GameManager.h"

int main() {

    Menu obj_m1;

    Board obj_p1;

    GameManager obj_gameManager(obj_p1);
    BoardManager obj_bm1(obj_p1, obj_gameManager);

    Clock obj_cl1;

    LevelCreator obj_lvlcreator(obj_p1);



    EventUpdate obj_eventUpdate(obj_m1, obj_p1, obj_cl1, obj_lvlcreator, obj_gameManager, obj_bm1);
    sfmlView obj_sfv1(obj_m1, obj_p1, obj_cl1, obj_lvlcreator, obj_bm1, obj_eventUpdate, obj_gameManager);



    return 0;
}
