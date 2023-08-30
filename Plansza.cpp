//
// Created by Wojtek on 24.08.2023.
//

#include "Plansza.h"

int const W = 22; //TOP
int const D = 3;  //RIGHT
int const S = 18; //BOTTOM
int const A = 0;  //LEFT
int const R = 17; //RESET LEVEL
int const P = 15; //LEVEL + 1
int const O = 14; //LEVEL - 1
int const Q = 16; //QUIT
int const N = 13; //QUIT



Plansza::Plansza() {
    width = 15;
    hight = 15;

    moveCounter = 0;

    wyczysc_Plansze();
}


void Plansza::wyczysc_Plansze() {

    moveCounter = 0;

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
        if (plansza[row][col].czyGracz == true) // PLAYER
            return 'Y';
        if (plansza[row][col].czyMina == true and plansza[row][col].czyUstawione == false) //BOX
            return 'X';
        if (plansza[row][col].czyUstawione == true and plansza[row][col].czyMina == true) //BOX AT GOOD PLACE
            return 'z';
        if (plansza[row][col].czySciana == true) //WALL
            return '#';
        if (plansza[row][col].czyOdkryte == false and plansza[row][col].czyUstawione == false and plansza[row][col].czyMina == false) //EMPTY SPACE
            return '.';
        if (plansza[row][col].czyUstawione == true and plansza[row][col].czyMina == false) // EMPTY SPACE FOR BOX
            return '-';
        if (plansza[row][col].czyUstawione == true and plansza[row][col].czyMina == true) // PLACE FOR BOX
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

        //Search player on board
        for (int row = 0; row < hight; row++) {
            for (int col = 0; col < width; col++) {
                if (plansza[row][col].czyGracz) {
                    playerRow = row;
                    playerCol = col;
                    break;
                }
            }
            if (playerRow != -1) //Player found, leave loop
                break;
        }

        int a = playerRow;
        int b = playerCol;

        int newRow = playerRow;
        int newCol = playerCol;



        //Make a player's move
        switch (move) {
            case W:
                if(playerRow - 1 < width and playerRow - 1 > 0){ //Checks if the player is off the board
                    newRow = playerRow - 1;
//                        moveCounter++;
                }
                break;
            case A:
                if(playerCol - 1 < hight and playerCol - 1 > 0){
                    newCol = playerCol - 1;
//                        moveCounter++;
                }

                break;
            case S:
                if(playerRow + 1 < width and playerRow + 1 > 0){
                    newRow = playerRow + 1;
//                        moveCounter++;
                }
                break;
            case D:
                if(playerCol + 1 < hight and playerCol + 1 > 0){
                    newCol = playerCol + 1;
//                        moveCounter++;
                }
                break;
            case R: //Resets the board to its initial state
                wyczysc_Plansze();
                moveCounter = 0;
                ustaw_Plansze();
                return;
            case P: //LEVEL + 1
                poziom++;
                ustaw_Plansze();
                cout <<poziom<<"---LEVEL NUMBER---" << endl;
                return;
            case O: //LEVEL - 1
                poziom--;
                ustaw_Plansze();
                cout <<"---LEVEL NUMBER---"<< poziom << endl;
                return;
            case N:
                wyczysc_Plansze();
                moveCounter = 0;
                ustaw_Plansze();
                break;
            case Q:
                exit(0); // Exit game
        }

        //Moves the player if there is no mine in front of him
        if (!plansza[newRow][newCol].czyMina) {
            plansza[playerRow][playerCol].czyGracz = false;
            plansza[newRow][newCol].czyGracz = true;
            //moveCounter++;
        }

        //Checks if the player collides with a wall
        if (plansza[newRow][newCol].czySciana) {
            plansza[playerRow][playerCol].czyGracz = true;
            plansza[newRow][newCol].czyGracz = false;
        }


        //Moves mine if there is no wall and mine in front of it
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

            //Moves mine
            plansza[newRow][newCol].czyMina = false;
            plansza[newMineRow][newMineCol].czyMina = true;

            //Moves the player
            plansza[playerRow][playerCol].czyGracz = false;
            plansza[newRow][newCol].czyGracz = true;


        }




        //checks if the boxes are in the right place
        if(check_win()){
            poziom++;
            ustaw_Plansze();
        }


    }

bool Plansza::check_win() {
    int boxCounter = 0;
    int winBoxCounter = 0;

    for(int row = 0; row < hight; row++)
        for(int col = 0; col < width; col++){
            if(plansza[row][col].czyMina)
                boxCounter++;
            if(get_Field_info(row,col) == 'z')
                winBoxCounter++;
        }

    if(winBoxCounter == boxCounter)
        return true;

    return false;
}

void Plansza::load_Map_File() {

    //clear map of char's
    map.clear();

    // Nazwa pliku z mapą
    string filename = "../Maps/map" + std::to_string(poziom) + ".txt";

    // Otwórz plik do odczytu
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Nie można otworzyć pliku." << endl;
        exit(0);
    }

    // Odczytaj zawartość pliku wiersz po wierszu
    string line;
    while (getline(file, line)) {
        vector<char> row;
        for (char c : line) {
            if (c != ' ') {
                row.push_back(c);
            }
        }
        map.push_back(row);
    }

    // Zamknij plik
    file.close();
}


void Plansza::przepisz_Mape_Do_Planszy(){
    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            Pole pole;
            char c = map[i][j];

            //pole.czyOdkryte = (c == '.');
            pole.czyGracz = (c == 'Y');
            pole.czyMina = (c == 'X');
            pole.czySciana = (c == '#');
            pole.czyUstawione = (c == '-');

            plansza[i][j] = pole;
        }
    }
}

void Plansza::ustaw_Plansze() {

    wyczysc_Plansze();
    load_Map_File();
    przepisz_Mape_Do_Planszy();

}

int Plansza::getPoziom() {
    return poziom;
}

int Plansza::getMoveCounter() {
    return moveCounter;
}

void Plansza::setPoziom(int p) {
    poziom = p;
}

void Plansza::setGracz(int row,int col, bool g) {
    plansza[row][col].czyGracz = g;
}

void Plansza::setSciana(int row, int col, bool s) {
    plansza[row][col].czySciana = s;
}

void Plansza::setMina(int row, int col, bool m) {
    plansza[row][col].czyMina = m;
}

void Plansza::setUstawione(int row, int col, bool u) {
    plansza[row][col].czyUstawione = u;
}

bool Plansza::getGracz(int row, int col) {
    return plansza[row][col].czyGracz;
}

bool Plansza::getMina(int row, int col) {
    return plansza[row][col].czyMina;
}

bool Plansza::getSciana(int row, int col) {
    return plansza[row][col].czySciana;
}

bool Plansza::getUstawione(int row, int col) {
    return plansza[row][col].czyUstawione;
}