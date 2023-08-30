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

sfmlView::sfmlView(Plansza & b, LevelCreator & l): obj_board1(b), obj_lvlCr1(l){
    width = 15;
    hight = 15;
    active_Board();
    widok();
}

void sfmlView::active_Board() {
    //Load textures
    for (int i = 0; i < 6; i++) {
        textures[i].loadFromFile("../Tekstury/pole" + std::to_string(i) + ".png");
    }

    if (!font.loadFromFile("../Tekstury/arial.ttf")) //Load font from file
        exit(0);

    //Text: Level
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10,10);

    //Text: Move
    text2.setFont(font);
    text2.setCharacterSize(24);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(150,10);

    //Resize the sprites vector to match the board dimensions
    sprites.resize(hight);
    for (int i = 0; i < hight; i++) {
        sprites[i].resize(width);
    }

    // Set sprite positions based on board layout
    for (int row = 0; row < hight; row++) {
        for (int col = 0; col < width; col++) {
            int x, y;
            x = 50 + 20 * col;
            y = 50 + 20 * row;
            sprites[row][col].setPosition(x, y);
        }
    }


}

void sfmlView::widok() {

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
            switch(obj_menu1.getGameStatus()){
                case PLAY:
                    if(!flag){
                        obj_board1.setPoziom(1);
                        obj_board1.ustaw_Plansze();
                        obj_clock.reset();
                        flag = true;
                    }
                    gameplay_update(event,flag);
                    break;

                case LEVELCREATOR:
                    //obj_board1.setPoziom(0);
                    if(!flag2){
                        obj_board1.wyczysc_Plansze();
                        obj_board1.setPoziom(0);
                        obj_board1.ustaw_Plansze();
                        flag2 = true;
                    }
                    level_creator_update(event,window, flag2);
                    break;
                case MENU:
                    menu_text_update(event,window);
                    break;
                case EXIT:
                    exit(0);
            }

        }

        //CLEAR DRAW DISPLAY - LOOP
        window.clear();

        if(obj_menu1.getGameStatus() == PLAY){
            // Aktualizuj stoper i wyświetl czas
            clock_text_update();
            window.draw(obj_clock.getText());


            RysujPlansze(window);
            draw_Text_Board(window);
        }

        if(obj_menu1.getGameStatus() == LEVELCREATOR){
            RysujPlansze(window);
            draw_Text_Creator(window);
        }


        if(obj_menu1.getGameStatus() == MENU)
            draw_Text_menu(window);

        window.display();


    }
}

char sfmlView::check_Input(int move) {
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


void sfmlView::gameplay_update(sf::Event event, bool &flag) {
    if (event.type == sf::Event::KeyPressed){
        int move;
        std::cout << "Key pressed: " << event.key.code << std::endl;
        move = event.key.code;
        cout << check_Input(move) << endl;
        obj_board1.update(move);
        if(check_Input(move) == 'N'){
            obj_menu1.setGameStatus(4);
            flag = false;
        }

        if(check_Input(move) == 'P' or check_Input(move) == 'O' or check_Input(move) == 'R' or obj_board1.check_win())
            obj_clock.reset();

    }
}

void sfmlView::clock_text_update() {
    float elapsedTime = obj_clock.getElapsedTime();
    obj_clock.setText(std::to_string(elapsedTime));
}

void sfmlView::menu_text_update(sf::Event event, sf::RenderWindow &win) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(win);

        // Sprawdź, czy kliknięcie jest w obszarze tekstu
        for(int i = 0; i < 3; i++)
            if (obj_menu1.getText(i).getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))){
                obj_menu1.setGameStatus(i+1);
        }
    }
}

void sfmlView::level_creator_update(sf::Event event, sf::RenderWindow &win,bool &flag2) {
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
                obj_menu1.setGameStatus(4);
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
                obj_board1.setSciana(row,col, true);
                break;
            case 'X': //BOX
                obj_board1.setMina(row,col, true);
                break;
            case 'C': //PLACE FOR BOX
                obj_board1.setUstawione(row,col, true);
                break;
            case 'V': //PLAYER
                obj_board1.setGracz(row,col,true);
                break;
            case 'B': //EREASE
                obj_board1.setSciana(row,col, false);
                obj_board1.setMina(row,col, false);
                obj_board1.setUstawione(row,col, false);
                obj_board1.setGracz(row,col,false);
                break;
        }


    }

}

void sfmlView::aktualizacjaPola(int row, int col){
    char stan_pola1 = obj_board1.get_Field_info(row, col);

    switch (stan_pola1)
    {
        case 'X': // BOX
            sprites[row][col].setTexture(textures[0]);
            break;
        case 'Y': //PLAYER
            sprites[row][col].setTexture(textures[1]);
            break;
        case '#': //WALL
            sprites[row][col].setTexture(textures[2]);
            break;
        case '-': //CHECKPOINT
            sprites[row][col].setTexture(textures[3]);
            break;
        case 'z': //CHECKPOINT AND BOX
            sprites[row][col].setTexture(textures[4]);
            break;
        case '.': //EMPTY SPACE
            sprites[row][col].setTexture(textures[5]);
            break;
        default:
            break;
    }
}



void sfmlView::RysujPlansze(sf::RenderWindow &win){

    //Drawing a board
    for (int wiersz = 0; wiersz < hight; wiersz++){
        for (int kolumna = 0; kolumna < width; kolumna++){
            aktualizacjaPola(wiersz, kolumna);
            //                win.draw(sprites[wiersz][kolumna]);
           // win.draw(Tablica[wiersz][kolumna]);
           win.draw(sprites[wiersz][kolumna]);

        }
    }
}

void sfmlView::draw_Text_menu(sf::RenderWindow &win) {
    for(int i = 0; i < 3; i++)
        win.draw(obj_menu1.getText(i));
}

void sfmlView::draw_Text_Creator(sf::RenderWindow &win) {
    for(int i = 0; i < 6; i++)
        win.draw(obj_lvlCr1.getText(i));
}

void sfmlView::draw_Text_Board(sf::RenderWindow &win) {
    //Drawing a text
    text.setString("Level: " + to_string(obj_board1.getPoziom()));
    text2.setString("Moves: " + to_string(obj_board1.getMoveCounter()));
    win.draw(text);
    win.draw(text2);
}
