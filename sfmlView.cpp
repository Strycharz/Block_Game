//
// Created by Wojtek on 25.08.2023.
//

#include "sfmlView.h"
#include <thread>
#include <atomic>


sfmlView::sfmlView(Plansza & b): obj_board1(b){
    width = 15;
    hight = 15;
    active_Board();
    widok();
}

char sfmlView::check_Input(int move) {
    switch(move){
        case 22: //TOP
            return 'W';
        case 18: //BOTTOM
            return 'S';
        case 0: //LEFT
            return 'A';
        case 3: //RIGHT
            return 'D';
        case 17: //RESET
            return 'R';
        case 15: //;LEVEL + 1
            return 'P';
    }

}



void sfmlView::widok() {

    sf::Clock clock;
    sf::Time elapsedTime;
    bool isRunning = true;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Block_Game");
//window.setVerticalSyncEnabled(false);
window.setFramerateLimit(60);
    int move;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (isRunning) {
                    elapsedTime += clock.getElapsedTime();
                    clock.restart();
                }
                isRunning = !isRunning;
            }

            if (isRunning) {
                sf::Time currentTime = clock.getElapsedTime();
                int totalSeconds = static_cast<int>((elapsedTime + currentTime).asSeconds());
                int minutes = totalSeconds / 60;
                int seconds = totalSeconds % 60;
                timerText.setString("Time: " + std::to_string(minutes) + "m " + std::to_string(seconds) + "s");
            }

   // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    // Klawisz A jest wciśnięty

            if (event.type == sf::Event::KeyPressed)
            {
                std::cout << "Key pressed: " << event.key.code << std::endl;
                move = event.key.code;
                cout << check_Input(move) << endl;
                obj_board1.update(move);
                obj_board1.debug_display();
                if('R' == check_Input(move))

                    window.clear();
            }
        }

        window.clear();
        RysujPlansze(window);
        window.display();


    }
}

void sfmlView::aktywuj_Plansze() {
        for (int i = 0; i < hight; i++)
            for (int j = 0; j < width; j++)
            {
                Tablica[i][j].setSize(sf::Vector2f(20, 20));
                Tablica[i][j].setFillColor(sf::Color::Blue);
                //Tablica[i][j].setOutlineColor(sf::Color::Blue);
               // Tablica[i][j].setOutlineThickness(3);
                Tablica[i][j].setPosition(50 + 30 * j, 50 + 30 * i);
            }
}
//
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

    //Text: Timer
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(250, 350);

    sprites.resize(hight);
    for (int i = 0; i < hight; i++) {
    sprites[i].resize(width);
}

for (int row = 0; row < hight; row++) {
    for (int col = 0; col < width; col++) {
        int x, y;
        x = 50 + 20 * col;
        y = 50 + 20 * row;
        sprites[row][col].setPosition(x, y);
    }
}


}

void sfmlView::aktualizacjaPola(int row, int col){
    char stan_pola1 = obj_board1.get_Field_info(row, col);

    switch (stan_pola1)
    {
        case 'X': // BOX
            //            cout << row <<endl;
            //            cout << col <<endl;
                       sprites[row][col].setTexture(textures[0]);
           // Tablica[row][col].setFillColor(sf::Color::Cyan);
            break;
            //--------------
        case 'Y': //PLAYER
           // Tablica[row][col].setFillColor(sf::Color::Red);
                      sprites[row][col].setTexture(textures[1]);
            break;
            //--------------
        case '#': //WALL
            //Tablica[row][col].setFillColor(sf::Color::Magenta);
                        sprites[row][col].setTexture(textures[2]);
            break;
            //--------------
        case '-': //CHECKPOINT
           // Tablica[row][col].setFillColor(sf::Color::White);
                       sprites[row][col].setTexture(textures[3]);
            break;
            //--------------
//        case 'O': //CHECKPOINT I MINA
//           // Tablica[row][col].setFillColor(sf::Color::Green);
//                     sprites[row][col].setTexture(textures[4]);
//            break;

        case 'z': //CHECKPOINT AND BOX
            // Tablica[row][col].setFillColor(sf::Color::Green);
            sprites[row][col].setTexture(textures[4]);
            break;
        case '.': //EMPTY SPACE
        sprites[row][col].setTexture(textures[5]);
            break;
        default:
            //            return;
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

    //Drawing a text
    text.setString("Level: " + to_string(obj_board1.getPoziom()));
    text2.setString("Moves: " + to_string(obj_board1.getMoveCounter()));
    win.draw(text);
    win.draw(text2);
    win.draw(timerText);
}

