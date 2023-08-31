//
// Created by Wojtek on 31.08.2023.
//

#include "EventUpdate.h"

enum STATUS {
    PLAY = 1,
    LEVELCREATOR,
    EXIT,
    MENU
};

EventUpdate::EventUpdate(Menu & m, Board & b, Clock & c, LevelCreator & l, GameManager & gm, BoardManager & bm): obj_menu1(m), obj_board1(b),
                                                                                                                 obj_clock(c), obj_lvlCr1(l), obj_boardManager(bm), obj_gameManager1(gm){
    
}

char EventUpdate::check_Input(int move) {
    switch(move){
        case 22:
            return 'W'; //TOP
        case 18:
            return 'S'; //BOTTOM
        case 0:
            return 'A'; //LEFT
        case 3:
            return 'D'; //RIGHT
        case 17:
            return 'R'; //RESET
        case 15:
            return 'P'; //LEVEL + 1
        case 14:
            return 'O'; //LEVEL - 1
        case 16:
            return 'Q'; //QUIT
        case 25:
            return 'Z'; //WALL
        case 23:
            return 'X'; //BOX
        case 2:
            return 'C'; //PLACE FOR BOX
        case 21:
            return 'V'; //PLAYER
        case 1:
            return 'B'; //EREASE
        case 12:
            return 'M'; //SAVE MAP
        case 13:
            return 'N'; //RETURN TO MENU
    }

}


void EventUpdate::gameplay_update(sf::Event event, bool &flag) {



    if(!flag){
        obj_gameManager1.setPoziom(1);
        obj_boardManager.init_board();
        obj_clock.reset();
        flag = true;
    }

    //Checks if the boxes are in the right place
    if(obj_gameManager1.check_win()){
        obj_gameManager1.level_up();
        obj_clock.reset();
        obj_boardManager.init_board();
    }

    if (event.type == sf::Event::KeyPressed){
        int move;
        std::cout << "code 79 Key pressed: " << event.key.code << std::endl;
        move = event.key.code;
        std::cout << check_Input(move) << std::endl;

        char choice = check_Input(move);

        switch(choice){
            case 'R': //Resets the board to its initial state
                obj_board1.clear_Board();
                obj_clock.reset();
                obj_boardManager.init_board();
                return;
            case 'P': //LEVEL + 1
                obj_gameManager1.level_up();
                obj_boardManager.init_board();
                obj_clock.reset();
                cout <<obj_gameManager1.getPoziom()<<"---LEVEL NUMBER---" << endl;
                return;
            case 'O': //LEVEL - 1
                obj_gameManager1.level_down();
                obj_boardManager.init_board();
                obj_clock.reset();
                cout <<"---LEVEL NUMBER---"<< obj_gameManager1.getPoziom() << endl;
                return;
            case 'N':
                obj_board1.clear_Board();
                obj_boardManager.init_board();
                obj_gameManager1.setGameStatus(MENU);
                flag = false;
                break;
            case 'Q':
                exit(0); // Exit game
        }

        obj_board1.update(move);


    }
}

void EventUpdate::clock_text_update() {
    float elapsedTime = obj_clock.getElapsedTime();
    obj_clock.setText(std::to_string(elapsedTime));
}

void EventUpdate::menu_text_update(sf::Event event, sf::RenderWindow &win) {
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(win);

        //Verify that the click is in the text area
        for(int i = 0; i < 3; i++)
            if (obj_menu1.getText(i).getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))){
                obj_gameManager1.setGameStatus(i+1);
            }
    }
}

void EventUpdate::level_creator_update(sf::Event event, sf::RenderWindow &win,bool &flag2) {

    if(!flag2){
        obj_board1.clear_Board();
        obj_gameManager1.setPoziom(0);
        obj_boardManager.init_board();
        flag2 = true;
    }

    if (event.type == sf::Event::KeyPressed){
        int move;
        move = event.key.code;
        choice = check_Input(move);
        switch(choice){
            case 'M': //SAVE MAP TO FILE
                obj_lvlCr1.save_to_file();
                return;
            case 'N': //RETURN TO MENU
                flag2 = false;
                obj_gameManager1.setGameStatus(MENU);
                break;
            case 'Q': //QUIT
                exit(0);
        }
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){

        sf::Vector2i mousePosition = sf::Mouse::getPosition(win);

        int col = (mousePosition.x - 50) / 20;
        int row = (mousePosition.y - 50) / 20;
        if (col >= 0 && col < width && row >= 0 && row < hight)
            switch(choice){
                case 'Z': //WALL
                    obj_board1.setWall(row,col, true);
                    break;
                case 'X': //BOX
                    obj_board1.setBox(row,col, true);
                    break;
                case 'C': //PLACE FOR BOX
                    obj_board1.setPlace(row,col, true);
                    break;
                case 'V': //PLAYER
                    obj_board1.setPlayer(row,col,true);
                    break;
                case 'B': //EREASE
                    obj_board1.setWall(row,col, false);
                    obj_board1.setBox(row,col, false);
                    obj_board1.setPlace(row,col, false);
                    obj_board1.setPlayer(row,col,false);
                    break;
            }


    }

}