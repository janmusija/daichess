//
// game.cpp
// 2026-034-05
// daichess
//

#include "core/game.h"
#include <string>


#define DISPLAYLEN 3

Game::Game(int x, int y){
    board.clear();
    players = {'w','b'};
    width = y;
    height = x;
    for (int i = 0; i<x; i++){
        std::vector<Piece*> tmp(y,nullptr);
        board.push_back(tmp);
    }
}

Game::Game(int x, int y, std::vector<char>&& p){
    board.clear();
    players = p;
    width = y;
    height = x;
    for (int i = 0; i<x; i++){
        std::vector<Piece*> tmp(y,nullptr);
        board.push_back(tmp);
    }
}

bool Game::placepiece(int x, int y, std::string betza, char tm){
    std::string b = betza;
    b.resize(DISPLAYLEN);
    return placepiece(x,y,b,betza,tm);
}

#include <iostream>
bool Game::placepiece(int x, int y, std::string disp, std::string betza, char tm){
    if (betza == ""){return 0;}
    else if (board.size() <= x || x < 0 || board[x].size() <= y || y < 0){return 0;}
    else {
        Piece pc = Piece(disp,betza,tm);
        board[x][y] = &pc;
        std::cout << x << ", " << y << "  ";
    }
    return 1;
}

Game default_daichess(){
    Game g = Game(16, 16);
    std::string start[8][16] {
        // lowest y                                   //highest y
        {"WB","WDD","R","FAA","NB","HFD","WFDNA","Z","Z","WFDNA","HFD","NR","FAA","R","WDD","WB"}, // highest x
        {"R","Z","FC","WF","FN","WC","B","Q","K","B","WC","FN","WF","FC","Z","R"},
        {"FD","B","WA","N","FD","WD","F","N","N","F","WD","FD","N","WA","B","FD"},
        {"P","P","P","P","P","P","P","P","P","P","P","P","P","P","P","P"},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""}                                          // lowest x
        /*
        mirror
        .
        .
        .
        */
    };
    std::string namestart[16][16] {
        // lowest y                                   //highest y
        {"WB ","WDD"," R ","FAA","NB ","HFD"," L "," Z "," Z "," L ","HFD","NR ","FAA"," R ","WDD","WB "}, // highest x
        {" R "," Z ","FC ","WF ","FN ","WC "," B "," Q "," K "," B ","WC ","FN ","WF ","FC "," Z "," R "},
        {"FD "," B ","WA "," N ","FD ","WD "," F "," N "," N "," F ","WD ","FD "," N ","WA "," B ","FD "},
        {" P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        /*
        mirror
        .
        .
        .
        */
    };
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++){
            int arrayx = (i<8)?i:15-i;
            std::string name = namestart[arrayx][j];
            if (i >=8){
                for (unsigned int k = 0; k<name.length(); k++){
                    name[k] += 'a'-'A';
                }
            }
            g.placepiece(i,j,name,start[arrayx][j],(i<8)?'w':'b'); // code...
        }
    }
    

    return g;
}

Piece* Game::get (std::string pos){
    return get(pos_algebraic(pos));
}

std::string algebraic_pos(int x, int y){ // rank is x coordinate!!
    std::string s;
    y+=1;
    while (y > 0) {
        --y;
        char d = 'a' + (y%26); 
        y/= 26;
        s = d + s;
    }
    return s + std::to_string(x + 1);
}
std::string algebraic_pos(std::pair<int,int> p){ return algebraic_pos(p.first,p.second);}

#include <iostream>
std::pair<int,int> pos_algebraic(std::string s){ // rank is x coord
    int x = -1;
    int y = -1;
    unsigned int bdry = 0;
    for (int i = 0; i<(int)s.length(); i++){
        if (s[i] >= '0' && s[i] <= '9'){
            bdry = i; break;
        }
    }
    std::cout << bdry << "!";
    x = std::atoi(s.substr(bdry).c_str()) - 1;
    std::string t = s.substr(0,bdry);
    if (bdry > 0){
        y = 0;
    }
    for (int i = 0; i<(int) t.length();i++){
        y*=26;
        y+=t[i]-'a'+1;
    }
    --y;
    

    return std::make_pair(x,y);
}

std::string Game::display_board(bool side){
    std::string s = std::to_string(height);
    if (!side) { 
    /*   rank
         +
         ^
         |
    - <--+--> + file
         |
         v
        -
    */
    for (int i = (int)height-1; i>=0; --i){
        for (int j = 0; j < (int)width; ++j){
            if (i >= 0 && j >= 0 && i<(int)board.size() && j < (int)board[i].size() && (board[i][j])){
                s= s+ board[i][j]->display;
            }
            else {s+= std::string(' ',DISPLAYLEN);}
            s+=' ';
        }
        s+= '\n';
    }
    } else {
    /*   rank
         -
         ^
         |
    + <--+--> - file
         |
         v
         +
    */
    for (int i = 0; i < (int)height; ++i){
        for (int j =(int)width-1; j >=0; --j){
            if (i >= 0 && j>= 0 && i<(int)board.size() && j < (int)board[i].size() && (board[i][j])){
                s= s+ board[i][j]->display;
            }
            else {s+= std::string(' ',DISPLAYLEN);}
            s+=' ';
        }
        s+= '\n';
    }
    }
    return s;
}