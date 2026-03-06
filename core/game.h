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
#include <memory>

class Game {
public:
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    unsigned int width; // i.e. number of files a - p
    unsigned int height; // i.e. number of ranks 1-16
    Game(int x,int y);
    Game(int x,int y, std::vector<char> &&p);
    std::vector<char> players;
    bool placepiece(int x, int y, std::string betza, char team);
    bool placepiece(int x, int y, std::string disp, std::string betza, char team);
    std::unique_ptr<Piece>* get (std::string);
    std::unique_ptr<Piece>* get(std::pair<int,int>xy){return & board[xy.first][xy.second];};
    std::unique_ptr<Piece>* get(int x, int y){return & board[x][y];};
    Piece* getpc (std::string s){return & (**get(s));};
    Piece* getpc(std::pair<int,int>xy){return & (**get(xy));};
    Piece* getpc(int x, int y){return & (**get(x,y));};
    std::string display_board(bool side);
    std::unordered_set<std::pair<int,int>,p_hash> accessible_moves(int x, int y, char curr_pl);
    std::unordered_set<std::pair<int,int>,p_hash> accessible_moves(std::pair<int,int> xy, char curr_pl){return accessible_moves(xy.first,xy.second,curr_pl);};
};

std::string algebraic_pos(int, int);
std::string algebraic_pos(std::pair<int,int> p);
std::pair<int,int> pos_algebraic(std::string s);
Game default_daichess();

std::string algebraic_x(int x);
std::string algebraic_y(int y);

#endif /* game.h */