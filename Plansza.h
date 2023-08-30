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
    void ustaw_Plansze();

    void load_Map_File();
    void przepisz_Mape_Do_Planszy();

    bool check_win();


    void debug_display();
    void update(char move);
    char get_Field_info( int row, int col);



    void setPoziom(int p);

    void setGracz(int row,int col, bool g);
    void setMina(int row,int col,bool m);
    void setSciana(int row,int col,bool s);
    void setUstawione(int row,int col,bool u);

    int getPoziom();
    int getMoveCounter();

    bool getGracz(int row, int col);
    bool getMina(int row, int col);
    bool getSciana(int row, int col);
    bool getUstawione(int row, int col);

};


#endif
