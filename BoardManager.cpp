//
// Created by Wojtek on 30.08.2023.
//

#include "BoardManager.h"

BoardManager::BoardManager(Board & b, GameManager & gm): obj_board1(b), obj_gameManager(gm) {
    active_board();
    active_text();
}

void BoardManager::active_board() {
//Load textures
    for (int i = 0; i < 6; i++) {
        textures[i].loadFromFile("../Tekstury/pole" + std::to_string(i) + ".png");
    }

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

void BoardManager::active_text(){
    if (!font.loadFromFile("../Tekstury/arial.ttf")) //Load font from file
        exit(0);

    //Text: Level
    text[0].setFont(font);
    text[0].setCharacterSize(24);
    text[0].setFillColor(sf::Color::White);
    text[0].setPosition(10,10);

    //Text: Move
    text[1].setFont(font);
    text[1].setCharacterSize(24);
    text[1].setFillColor(sf::Color::White);
    text[1].setPosition(150,10);
}

std::vector<std::vector<sf::Sprite>> BoardManager::getSprite(){
    return sprites;
}

sf::Text BoardManager::getText(int i) {
    return text[i];
}

void BoardManager::field_update(int row, int col) {
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

void BoardManager::setText() {
    text[0].setString("Level: " + to_string(obj_gameManager.getPoziom()));
    text[1].setString("Moves: " + to_string(obj_board1.getMoveCounter()));
}

void BoardManager::load_Map_File() {

    //clear map of char's
    map.clear();

    //The name of the map file
    string filename = "../Maps/map" + std::to_string(obj_gameManager.getPoziom()) + ".txt";

    //Open the file for reading
    ifstream file(filename);

    if (!file.is_open()) {
        cout <<"The file cannot be opened." << endl;
        exit(0);
    }

    //Read the contents of the file line by line
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


void BoardManager::rewrite_Map_To_Board(){
    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            Field field;
            char c = map[i][j];

            //field.czyOdkryte = (c == '.');
            field.isPlayer = (c == 'Y');
            field.isBox= (c == 'X');
            field.isWall = (c == '#');
            field.isPlace = (c == '-');

            obj_board1.setField(field,i,j);
        }
    }
}

void BoardManager::init_board() {
    obj_board1.clear_Board();
    load_Map_File();
    rewrite_Map_To_Board();
}