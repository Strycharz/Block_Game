#include <iostream>

#include <SFML/Graphics.hpp>


#include "Plansza.h"
#include "sfmlView.h"
#include "LevelCreator.h"



int main() {

    Plansza obj_p1;

    LevelCreator obj_lvlcreator(obj_p1);

    sfmlView obj_sfv1(obj_p1,obj_lvlcreator);


    return 0;
}
