//
// Created by Wojtek on 24.08.2023.
//

#include "Board.h"

int const W = 22; //TOP
int const D = 3;  //RIGHT
int const S = 18; //BOTTOM
int const A = 0;  //LEFT
int const R = 17; //RESET LEVEL
int const P = 15; //LEVEL + 1
int const O = 14; //LEVEL - 1
int const Q = 16; //QUIT
int const N = 13; //QUIT



Board::Board() {
    width = 15;
    hight = 15;

    moveCounter = 0;

    clear_Board();
}


void Board::clear_Board() {

    moveCounter = 0;

    for (int wiersz = 0; wiersz < hight; wiersz++) {
        for (int kolumna = 0; kolumna < width; kolumna++) {
            board[wiersz][kolumna].isUncovered = false;
            board[wiersz][kolumna].isPlayer = false;
            board[wiersz][kolumna].isBox = false;
            board[wiersz][kolumna].isWall = false;
            board[wiersz][kolumna].isPlace = false;
        }
    }

}

char Board::get_Field_info(int row, int col) {

    {
        if (board[row][col].isPlayer == true) // PLAYER
            return 'Y';
        if (board[row][col].isBox == true and board[row][col].isPlace == false) //BOX
            return 'X';
        if (board[row][col].isPlace == true and board[row][col].isBox == true) //BOX AT GOOD PLACE
            return 'z';
        if (board[row][col].isWall == true) //WALL
            return '#';
        if (board[row][col].isUncovered == false and board[row][col].isPlace == false and board[row][col].isBox == false) //EMPTY SPACE
            return '.';
        if (board[row][col].isPlace == true and board[row][col].isBox == false) // EMPTY SPACE FOR BOX
            return '-';
        if (board[row][col].isPlace == true and board[row][col].isBox == true) // PLACE FOR BOX
            return 'O';

        return ' ';

    }
}


void Board::debug_display(){
    for (int row = 0; row < hight; row++) {
        for (int col = 0; col < width; col++) {
            cout << get_Field_info(row, col) << " ";
        }
        cout << endl;
    }
    cout << "----------------------------------------------" << endl;
}


void Board::update(char move) {


        //cout << "W, A, S, D - ruch, R - reset planszy, Q - wyjscie, : ";
        //move = cin.get(); // Używamy

        int playerRow = -1;
        int playerCol = -1;

        //Search player on board
        for (int row = 0; row < hight; row++) {
            for (int col = 0; col < width; col++) {
                if (board[row][col].isPlayer) {
                    playerRow = row;
                    playerCol = col;
                    break;
                }
            }
            if (playerRow != -1) //Player found, leave loop
                break;
        }


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

        }

        //Moves the player if there is no mine in front of him
        if (!board[newRow][newCol].isBox) {
            board[playerRow][playerCol].isPlayer = false;
            board[newRow][newCol].isPlayer = true;
            //moveCounter++;
        }

        //Checks if the player collides with a wall
        if (board[newRow][newCol].isWall) {
            board[playerRow][playerCol].isPlayer = true;
            board[newRow][newCol].isPlayer = false;
        }


        //Moves mine if there is no wall and mine in front of it
        if(board[newRow][newCol].isBox){
            int newMineRow;
            int newMineCol;

            switch (move) {
                case W:
                    if(!board[playerRow-2][newCol].isWall && !board[playerRow-2][newCol].isBox){
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
                    if(!board[newRow][playerCol - 2].isWall && !board[newRow][playerCol - 2].isBox){
                        newMineCol = playerCol - 2;
                        newMineRow = playerRow;
                    }else{
                        newMineRow = newRow;
                        newMineCol = newCol;

                        newCol = newCol + 1;
                    }
                    break;
                case S:
                    if(!board[playerRow + 2][newCol].isWall && !board[playerRow + 2][newCol].isBox){
                        newMineRow = playerRow + 2;
                        newMineCol = playerCol;
                    }else{
                        newMineRow = newRow;
                        newMineCol = newCol;

                        newRow = newRow - 1;
                    }
                    break;
                case D:
                    if(!board[newRow][playerCol + 2].isWall && !board[newRow][playerCol + 2].isBox){
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
            board[newRow][newCol].isBox = false;
            board[newMineRow][newMineCol].isBox = true;

            //Moves the player
            board[playerRow][playerCol].isPlayer = false;
            board[newRow][newCol].isPlayer = true;


        }


    }



int Board::getMoveCounter() {
    return moveCounter;
}


void Board::setPlayer(int row, int col, bool g) {
    board[row][col].isPlayer = g;
}

void Board::setWall(int row, int col, bool s) {
    board[row][col].isWall = s;
}

void Board::setBox(int row, int col, bool m) {
    board[row][col].isBox = m;
}

void Board::setPlace(int row, int col, bool u) {
    board[row][col].isPlace = u;
}

void Board::setField(Field field, int row, int col) {
    board[row][col] = field;
}

bool Board::getPlayer(int row, int col) {
    return board[row][col].isPlayer;
}

bool Board::getBox(int row, int col) {
    return board[row][col].isBox;
}

bool Board::getWall(int row, int col) {
    return board[row][col].isWall;
}

bool Board::getPlace(int row, int col) {
    return board[row][col].isPlace;
}