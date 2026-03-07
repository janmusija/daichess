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
#include <unordered_map>
#include <memory>


std::string algebraic_pos(int, int);
std::string algebraic_pos(std::pair<int,int> p);
std::pair<int,int> pos_algebraic(std::string s);

class Game {
public:
    std::vector<std::vector<std::unique_ptr<Piece>>> board;
    bool withinbounds(int x, int y){
        return (x>= 0 && x < (int) board.size() && y >= 0 && y<(int) board[x].size());
    }
    bool haspiece(int x, int y){
        return withinbounds(x,y)&&(board[x][y]);
    }
    unsigned int width; // i.e. number of files a - p
    unsigned int height; // i.e. number of ranks 1-16
    std::string algebraic_history; //move history of the game
    std::unordered_map<char,std::pair<int,int>> royals; // positions of royal pieces
    Game(int x,int y);
    Game(int x,int y, std::vector<char> &&p);
    std::vector<char> players;
    bool placepiece(int x, int y, std::string betza, char team);
    bool placepiece(int x, int y, std::string disp, std::string betza, char team);
    std::unique_ptr<Piece>* get (std::string s) {return get(pos_algebraic(s));};
    std::unique_ptr<Piece>* get(std::pair<int,int>xy){return & board[xy.first][xy.second];};
    std::unique_ptr<Piece>* get(int x, int y){
        if (withinbounds(x,y)){
            return & board[x][y];
        } else {return nullptr;}
    };
    Piece* getpc (std::string s){return getpc(pos_algebraic(s));};
    Piece* getpc(std::pair<int,int>xy){return getpc(xy.first,xy.second);};
    Piece* getpc(int x, int y){
        if (haspiece(x,y)){
            return & (**get(x,y));
        } else {
            return nullptr;
        }
    };

    // gets the on-board moves for a piece. does not account for check
    std::unordered_set<std::pair<int,int>,p_hash> accessible_moves(int x, int y, char curr_pl);
    std::unordered_set<std::pair<int,int>,p_hash> accessible_moves(std::pair<int,int> xy, char curr_pl){return accessible_moves(xy.first,xy.second,curr_pl);};
    bool accesses(int x0, int y0, int x1, int y1);// does not account for check

    bool incheck(char pl);
    bool hasmoves(char pl);
    std::unordered_set<std::pair<int,int>,p_hash> checkless_moves(int x, int y, char curr_pl);
    std::unordered_set<std::pair<int,int>,p_hash> checkless_moves(std::pair<int,int> xy, char curr_pl);


    // utility info
    std::string display_board(bool side);
    std::string display_moves(int x, int y);
    std::string display_moves(std::pair<int,int>xy){return display_moves(xy.first,xy.second);};
    std::string display_moves(std::string s) {return display_moves(pos_algebraic(s));};

    // make a move (without regard for legality)
    bool mov(int x0, int y0, int x1, int y1);
    bool mov(std::pair<int,int>xy0, std::pair<int,int>xy1){return mov(xy0.first,xy0.second,xy1.first,xy1.second);};
    bool mov(std::string s0, std::string s1){return mov(pos_algebraic(s0),pos_algebraic(s1));};
};

Game default_daichess();

std::string algebraic_x(int x);
std::string algebraic_y(int y);

#endif /* game.h */