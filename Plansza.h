//
// Created by Wojtek on 24.08.2023.
//

#ifndef GIERKASFML_PLANSZA_H
#define GIERKASFML_PLANSZA_H


#include <iostream>
#include <conio.h> //Added to getch() support on Windows
#include <vector>
#include <fstream>

using namespace std;

struct Pole {
    bool czyOdkryte;
    bool czyGracz;
    bool czyMina;
    bool czySciana;
    bool czyUstawione;

};

class Plansza {
   int width;
   int hight;

   int poziom;
    Pole plansza[15][15];

    //Vector storing the map
    vector<vector<char>> map;

    int moveCounter;


public:
    Plansza();

    void wyczysc_Plansze();
    void ustaw_Plansze(int poziom);

    bool check_win();


    void debug_display();
    void update(char move);

    char get_Field_info( int row, int col);

    void load_Map_File();


    int getPoziom();
    int getMoveCounter();

    void przepisz_Mape_Do_Planszy();
};


#endif //GIERKASFML_PLANSZA_H
