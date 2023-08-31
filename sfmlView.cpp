//
// Created by Wojtek on 25.08.2023.
//

#include "sfmlView.h"


enum STATUS {
    PLAY = 1,
    LEVELCREATOR,
    EXIT,
    MENU
};

sfmlView::sfmlView(Menu & m, Board & b, Clock & c, LevelCreator & l, BoardManager & bm, EventUpdate & ev, GameManager & gm): obj_menu1(m), obj_board1(b), obj_bm1(bm), obj_clock(c), obj_lvlCr1(l), obj_eventUp1(ev), obj_gameManager(gm){
    width = 15;
    height = 15;

    view();
}



void sfmlView::view() {

    sf::RenderWindow window(sf::VideoMode(400, 400), "Block_Game");
    //window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
    bool flag = false;
    bool flag2 = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //Handle different game states
            switch(obj_gameManager.getGameStatus()){
                case PLAY:
                    obj_eventUp1.gameplay_update(event,flag);
                    break;
                case LEVELCREATOR:
                    obj_eventUp1.level_creator_update(event,window, flag2);
                    break;
                case MENU:
                    obj_eventUp1.menu_text_update(event,window);
                    break;
                case EXIT:
                    exit(0);
            }

        }

        //CLEAR DRAW DISPLAY - LOOP
        window.clear();

        if(obj_gameManager.getGameStatus() == PLAY){
            draw_Board(window);
            draw_Text_Board(window);
            draw_Text_Clock(window);
        }

        if(obj_gameManager.getGameStatus() == LEVELCREATOR){
            draw_Board(window);
            draw_Text_Creator(window);
        }

        if(obj_gameManager.getGameStatus() == MENU)
            draw_Text_menu(window);

        window.display();


    }
}


void sfmlView::draw_Text_menu(sf::RenderWindow &win) {
    for(int i = 0; i < 3; i++)
        win.draw(obj_menu1.getText(i));
}

void sfmlView::draw_Board(sf::RenderWindow &win){

    //Drawing a board
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            obj_bm1.field_update(row,col);
           win.draw(obj_bm1.getSprite()[row][col]);

        }
    }
}

void sfmlView::draw_Text_Board(sf::RenderWindow &win) {
    //Drawing a text
    obj_bm1.setText();
    win.draw(obj_bm1.getText(0));
    win.draw(obj_bm1.getText(1));
}

void sfmlView::draw_Text_Clock(sf::RenderWindow &win) {
    //Update stopwatch and view time
    obj_eventUp1.clock_text_update();
    win.draw(obj_clock.getText());
}

void sfmlView::draw_Text_Creator(sf::RenderWindow &win) {
    for(int i = 0; i < 6; i++)
        win.draw(obj_lvlCr1.getText(i));
}


