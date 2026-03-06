//
// game.h
// 2026-03-05
// daichess
//

// API for gameboards

#ifndef game_h 
#define game_h
#include "core/piece.h"
#include <vector>

class Game {
public:
    std::vector<std::vector<Piece*>> board;
    unsigned int width; // i.e. number of files a - p
    unsigned int height; // i.e. number of ranks 1-16
    Game(int x,int y);
    Game(int x,int y, std::vector<char> &&p);
    std::vector<char> players;
    bool placepiece(int x, int y, std::string betza, char team);
    bool placepiece(int x, int y, std::string disp, std::string betza, char team);
    Piece* get (std::string);
    Piece* get(std::pair<int,int>xy){return board[xy.first][xy.second];};
    Piece* get(int x, int y){return board[x][y];};
    std::string display_board(bool side);
};

std::string algebraic_pos(int, int);
std::string algebraic_pos(std::pair<int,int> p);
std::pair<int,int> pos_algebraic(std::string s);

Game default_daichess();

#endif /* game.h */