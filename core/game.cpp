//
// game.cpp
// 2026-034-05
// daichess
//

#include "core/game.h"
#include <string>

Game::Game(int x, int y){
    std::vector<char> p = {'w','b'};
    Game(x,y,std::move(p));
}

Game::Game(int x, int y, std::vector<char>&& p){
    players = p;
    width = x;
    height = y;
}

void Game::placepiece(int x, int y, std::string betza){
    if (betza == ""){return;}
    else {
        
    }
}

Game default_daichess(){
    Game g = Game(16, 16);
    std::string start[16][16] {
        // lowest y                                   //highest y
        {"WB","WDD","R","FAA","NB","HFD","WFDNA","Z","Z","WFDNA","HFD","NR","FAA","R","WDD","WB"}, // highest x
        {"R","Z","FC","WF","FN","WC","B","Q","K","B","WC","FN","WF","FC","Z","R"},
        {"FD","B","WA","N","FD","WD","F","N","N","F","WD","FD","N","WA","B","FD"},
        {"P","P","P","P","P","P","P","P","P","P","P","P","P","P","P","P"},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""}
        /*
        mirror
        .
        .
        .
        */
    };
    

    return g;
}

Piece* Game::get (std::string pos){
    
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
    for (int i = 0; i<s.length(); i++){
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
    for (int i = 0; i<t.length();i++){
        y*=26;
        y+=t[i]-'a'+1;
    }
    --y;
    

    return std::make_pair(x,y);
}