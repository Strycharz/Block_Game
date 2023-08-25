//
// Created by Wojtek on 25.08.2023.
//

#include "sfmlView.h"



sfmlView::sfmlView(Plansza & b): obj_board1(b){
    width = 15;
    hight = 15;
    active_Board();
  //  aktywuj_Plansze();
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
    }

}

void sfmlView::widok() {



    sf::RenderWindow window(sf::VideoMode(800, 600), "Keyboard Input Example");
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


   // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    // Klawisz A jest wciśnięty

            if (event.type == sf::Event::KeyPressed)
            {
                std::cout << "Key pressed: " << event.key.code << std::endl;
                move = event.key.code;
                cout << check_Input(move) << endl;
                obj_board1.update(move);
                obj_board1.debug_display();
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
    //laduje tekstury
   for (int i = 0; i < 6; i++) {
       textures[i].loadFromFile("C:/Users/Wojtek/Desktop/GierkaSFML/Tekstury/pole" + std::to_string(i) + ".png");
        //0 - 8 number of bombs around, 9 - default, 10 - bomb, 11 - flag
    }

    sprites.resize(hight);
    for (int i = 0; i < hight; i++) {
    sprites[i].resize(width);
}

for (int wiersz = 0; wiersz < hight; wiersz++) {
    for (int kolumna = 0; kolumna < width; kolumna++) {
        int x, y;
        x = 50 + 20 * kolumna;
        y = 50 + 20 * wiersz;
        sprites[wiersz][kolumna].setPosition(x, y);
    }
}


}

void sfmlView::aktualizacjaPola(int row, int col){
    char stan_pola1 = obj_board1.get_Field_info(row, col);

    switch (stan_pola1)
    {
        case 'X': // SKRZYNIA
            //            cout << row <<endl;
            //            cout << col <<endl;
                       sprites[row][col].setTexture(textures[0]);
           // Tablica[row][col].setFillColor(sf::Color::Cyan);
            break;
            //--------------
        case 'Y': //GRACZ
           // Tablica[row][col].setFillColor(sf::Color::Red);
                      sprites[row][col].setTexture(textures[1]);
            break;
            //--------------
        case '#': //SCIANA
            //Tablica[row][col].setFillColor(sf::Color::Magenta);
                        sprites[row][col].setTexture(textures[2]);
            break;
            //--------------
        case '-': //CHECKPOINT
           // Tablica[row][col].setFillColor(sf::Color::White);
                       sprites[row][col].setTexture(textures[3]);
            break;
            //--------------
        case 'O': //CHECKPOINT I MINA
           // Tablica[row][col].setFillColor(sf::Color::Green);
                     sprites[row][col].setTexture(textures[4]);
            break;
        case '.':
        sprites[row][col].setTexture(textures[5]);
            break;
        default:
            //            return;
            break;
    }
}

void sfmlView::RysujPlansze(sf::RenderWindow &win){

    // tu robimy rysowanie planszy na podstawie zawartości "board"
    for (int wiersz = 0; wiersz < hight; wiersz++)
    {
        for (int kolumna = 0; kolumna < width; kolumna++)
        {
            aktualizacjaPola(wiersz, kolumna);
            //                win.draw(sprites[wiersz][kolumna]);
           // win.draw(Tablica[wiersz][kolumna]);
           win.draw(sprites[wiersz][kolumna]);
        }
    }

}

