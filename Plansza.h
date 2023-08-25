//
// Created by Wojtek on 24.08.2023.
//

#ifndef GIERKASFML_PLANSZA_H
#define GIERKASFML_PLANSZA_H


#include <iostream>
#include <conio.h> // Dodane do obslugi funkcji getch() w systemie Windows
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

    Pole  plansza[15][15];

public:
    Plansza();

    void wyczysc_Plansze();
    void ustaw_Plansze();


    void debug_display();
    void update(char move);

    char get_Field_info( int row, int col);

    void petla();
};


#endif //GIERKASFML_PLANSZA_H
