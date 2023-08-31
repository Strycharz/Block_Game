//
// Created by Wojtek on 24.08.2023.
//

#ifndef GIERKASFML_BOARD_H
#define GIERKASFML_BOARD_H


#include <iostream>
#include <conio.h> //Added to getch() support on Windows
#include <vector>
#include <fstream>

using namespace std;

struct Field {
    bool isUncovered;
    bool isPlayer;
    bool isBox;
    bool isWall;
    bool isPlace;

};

class Board {
   int width;
   int height;


    Field board[15][15];


    int moveCounter;


public:
    Board();
    void clear_Board();


    void debug_display();
    void update(char move);
    char get_Field_info( int row, int col);



    void setPlayer(int row,int col, bool g);
    void setBox(int row,int col,bool m);
    void setWall(int row,int col,bool s);
    void setPlace(int row,int col,bool u);
    void setField(Field f, int row, int col);


    int getMoveCounter();

    bool getPlayer(int row, int col);
    bool getBox(int row, int col);
    bool getWall(int row, int col);
    bool getPlace(int row, int col);

};


#endif
