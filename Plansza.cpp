//
// Created by Wojtek on 24.08.2023.
//

#include "Plansza.h"

int const W = 22;
int const D = 3;
int const S = 18;
int const A = 0;

Plansza::Plansza() {
    width = 15;
    hight = 15;

    wyczysc_Plansze();
    ustaw_Plansze();

    poziom = 1;
}

void Plansza::petla() {

}

void Plansza::wyczysc_Plansze() {

    for (int wiersz = 0; wiersz < hight; wiersz++) {
        for (int kolumna = 0; kolumna < width; kolumna++) {
            plansza[wiersz][kolumna].czyOdkryte = false;
            plansza[wiersz][kolumna].czyGracz = false;
            plansza[wiersz][kolumna].czyMina = false;
            plansza[wiersz][kolumna].czySciana = false;
            plansza[wiersz][kolumna].czyUstawione = false;
        }
    }

}

char Plansza::get_Field_info(int row, int col) {

    {
        if (plansza[row][col].czyGracz == true)
            return 'Y';
        if (plansza[row][col].czyMina == true and plansza[row][col].czyUstawione == false)
            return 'X';
        if (plansza[row][col].czySciana == true)
            return '#';
        if (plansza[row][col].czyOdkryte == false and plansza[row][col].czyUstawione == false and plansza[row][col].czyMina == false)
            return '.';
        if (plansza[row][col].czyUstawione == true and plansza[row][col].czyMina == false)
            return '-';
        if (plansza[row][col].czyUstawione == true and plansza[row][col].czyMina == true)
            return 'O';

        return ' ';

    }
}


void Plansza::debug_display(){
    for (int row = 0; row < hight; row++) {
        for (int col = 0; col < width; col++) {
            cout << get_Field_info(row, col) << " ";
        }
        cout << endl;
    }
    cout << "----------------------------------------------" << endl;
}


void Plansza::update(char move) {


        //cout << "W, A, S, D - ruch, R - reset planszy, Q - wyjscie, : ";
        //move = cin.get(); // Używamy

        int playerRow = -1;
        int playerCol = -1;

        // Znajdź pozycję gracza na planszy
        for (int row = 0; row < hight; row++) {
            for (int col = 0; col < width; col++) {
                if (plansza[row][col].czyGracz) {
                    playerRow = row;
                    playerCol = col;
                    break;
                }
            }
            if (playerRow != -1) // Gracz znaleziony, opuść pętlę
                break;
        }

//        for(int roww=0; roww < hight; roww++)
//            for(int coll=0; coll < width; coll++)
//                plansza[roww][coll].czyGracz = false;
//
//        plansza[playerRow][playerCol].czyGracz = true;

        int newRow = playerRow;
        int newCol = playerCol;

        // Wykonaj ruch gracza
        switch (move) {
            case W:
                newRow = playerRow - 1;
                break;
            case A:
                newCol = playerCol - 1;
                break;
            case S:
                newRow = playerRow + 1;
                break;
            case D:
                newCol = playerCol + 1;
                break;
//            case 'r': // Resetuje plansze do stanu poczatkowego
//                ustaw_Plansze();
//                return;
//            case 'p':
//                poziom++;
//                cout <<poziom<<"ddddddddddddddddddd" << endl;
//                return;
//            case 'q':
//                exit(0); // Wyjście z gry
        }

        //przesowa gracza, jesli nie ma przed nim miny
        if (!plansza[newRow][newCol].czyMina) {
            plansza[playerRow][playerCol].czyGracz = false;
            plansza[newRow][newCol].czyGracz = true;
        }

        //sprawdza czy gracz nie koliduje z sciana
        if (plansza[newRow][newCol].czySciana) {
            plansza[playerRow][playerCol].czyGracz = true;
            plansza[newRow][newCol].czyGracz = false;
        }


        //przesowa mine, jesli nie ma przed nia sciany
        if(plansza[newRow][newCol].czyMina){
            int newMineRow;
            int newMineCol;

            switch (move) {
                case W:
                    if(!plansza[playerRow-2][newCol].czySciana && !plansza[playerRow-2][newCol].czyMina){
                        newMineRow = playerRow - 2;
                        newMineCol = playerCol;
                    }
                    else{
                        newMineRow = newRow;
                        newMineCol = newCol;

                        newRow = newRow + 1;
                    }
                    break;
                case A:
                    if(!plansza[newRow][playerCol - 2].czySciana && !plansza[newRow][playerCol - 2].czyMina){
                        newMineCol = playerCol - 2;
                        newMineRow = playerRow;
                    }else{
                        newMineRow = newRow;
                        newMineCol = newCol;

                        newCol = newCol + 1;
                    }
                    break;
                case S:
                    if(!plansza[playerRow + 2][newCol].czySciana && !plansza[playerRow + 2][newCol].czyMina){
                        newMineRow = playerRow + 2;
                        newMineCol = playerCol;
                    }else{
                        newMineRow = newRow;
                        newMineCol = newCol;

                        newRow = newRow - 1;
                    }
                    break;
                case D:
                    if(!plansza[newRow][playerCol + 2].czySciana && !plansza[newRow][playerCol + 2].czyMina){
                        newMineCol = playerCol + 2;
                        newMineRow = playerRow;
                    }else{
                        newMineRow = newRow;
                        newMineCol = newCol;

                        newCol = newCol - 1;
                    }
                    break;

            }

            //przesówa mine
            plansza[newRow][newCol].czyMina = false;
            plansza[newMineRow][newMineCol].czyMina = true;

            //przesówa gracza
            plansza[playerRow][playerCol].czyGracz = false;
            plansza[newRow][newCol].czyGracz = true;


        }


        // Odśwież planszę
        //system("cls"); // Wyczyść ekran (Windows)





    }

void Plansza::ustaw_Plansze() {


//plansza[0][0].czyGracz = true;
//
//plansza[2][2].czyMina = true;
//plansza[2][3].czyMina = true;
//
//plansza[5][5].czySciana = true;
//plansza[5][6].czySciana = true;
            cout <<poziom<<" costamss-ssssssss " <<endl;
            plansza[7][1].czyGracz = true;

            plansza[5][2].czyMina = true;
            plansza[6][2].czyMina = true;
            plansza[6][3].czyMina = true;

            plansza[3][7].czyUstawione = true;
            plansza[4][7].czyUstawione = true;
            plansza[5][7].czyUstawione = true;
//I
            plansza[4][0].czySciana = true;
            plansza[5][0].czySciana = true;
            plansza[6][0].czySciana = true;
            plansza[7][0].czySciana = true;
            plansza[8][0].czySciana = true;
//II
            plansza[0][1].czySciana = true;
            plansza[1][1].czySciana = true;
            plansza[2][1].czySciana = true;
            plansza[3][1].czySciana = true;
            plansza[4][1].czySciana = true;
            plansza[8][1].czySciana = true;
//III
            plansza[0][2].czySciana = true;
            plansza[3][2].czySciana = true;
            plansza[4][2].czySciana = true;
            plansza[8][2].czySciana = true;
//IV
            plansza[0][3].czySciana = true;
            plansza[8][3].czySciana = true;

//V
            plansza[0][4].czySciana = true;
            plansza[4][4].czySciana = true;
            plansza[5][4].czySciana = true;
            plansza[6][4].czySciana = true;
            plansza[7][4].czySciana = true;
            plansza[8][4].czySciana = true;

//VI
            plansza[0][5].czySciana = true;
            plansza[1][5].czySciana = true;
            plansza[2][5].czySciana = true;
            plansza[4][5].czySciana = true;

            plansza[1][6].czySciana = true;
            plansza[4][6].czySciana = true;
            plansza[5][6].czySciana = true;
            plansza[6][6].czySciana = true;

            plansza[1][7].czySciana = true;
            plansza[6][7].czySciana = true;

            plansza[1][8].czySciana = true;
            plansza[2][8].czySciana = true;
            plansza[3][8].czySciana = true;
            plansza[4][8].czySciana = true;
            plansza[5][8].czySciana = true;
            plansza[6][8].czySciana = true;

        }







