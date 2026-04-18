//
// engines.h
// 2026-03-05
// daichess
//

// defines a list of chess engines ("engine" may be a stretch. more like... thing that does chess.)

#ifndef engines_h
#define engines_h

#include "core/game.h"
#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <limits>
#include <math.h>
#include <functional>
#include "engine/game_man.h"

// tk

class Engine {
public:
    virtual std::pair<std::pair<int,int>,std::pair<int,int>> underlying_move(Game & g, char pl) = 0; // make a legal move in a given position (technically you could make an engine that cheats, I guess). return 1 if successful; otherwise forfeit.
    virtual std::string underlying_prom(Game & g, int x1, int y1, char pl) = 0; // promote
    bool e_move(Game & g, char pl); // wrapped with miscellaneous details to ensure the move is processed properly
    std::string e_prom(Game & g, int x1, int y1, char pl); // promotion
    char fc;
    void setfacing (char f){fc = f;}
};

class random_move : public Engine {
    /*
    makes a random legal move.
    */
public:
    std::pair<std::pair<int,int>,std::pair<int,int>> underlying_move(Game & g, char pl);
    std::string underlying_prom(Game & g, int x1, int y1, char pl);
    std::mt19937 rng;
    random_move(int seed){
        rng = std::mt19937(seed);
    }
    random_move(){
        rng = std::mt19937(time(nullptr));
    }
};

std::pair<int,int> pick_random_member(const std::unordered_set<std::pair<int,int>,p_hash>& options, std::mt19937& rng); 
/*
really i should template this.
template <typename T, typename T_hash> T pick_random_member(const std::unordered_set<T,T_hash>& options, std::mt19937& rng) or something idk
*/
std::pair<std::pair<int,int>,std::pair<int,int>> pick_random_member(const std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash>& options, std::mt19937& rng);

class CCCP : public Engine { // per tom7
    /*
    makes a move according to the following priorities:
    - checkmate opponent
    - check opponent
    - capture a piece
    - push a piece
    */
public:
    std::pair<std::pair<int,int>,std::pair<int,int>> underlying_move(Game & g, char pl);
    std::string underlying_prom(Game & g, int x1, int y1, char pl);
    unsigned short tiebreak = 2; // to prevent getting stuck in a loop
};

float move_count_heuristic(Piece & p, const int boardsize); // for a piece's value. TODO: make better
inline float ride_bonus(int x, int y, int len, const int boardsize);

#define BOARDSIZE_FOR_ALGO 16

float quick_heuristic(const Game & g, char pl, float & next_p_tot, float & prev_p_tot, std::unordered_map<std::string,float> & val_cache); // designed for a two player game. pl is the player to move = next_p.
// evaluates the game for the next player.

class basic_search_algo : public Engine {
    /*
    makes a move by first trying all its possible moves, then trying all your possible moves. searches tree to a depth of [depth] moves (counting players' moves separately).
    at the end, chooses whatever minmaxes value.
    */
public:
    std::pair<std::pair<int,int>,std::pair<int,int>> underlying_move(Game & g, char pl);
    std::string underlying_prom(Game & g, int x1, int y1, char pl);
    std::unordered_map<std::string,float> val_cache;
    std::string promcache;

    std::pair<float,std::string> find_best_move(unsigned int lev,Game_Man & gm);

    unsigned int depth; // how deep to search
    basic_search_algo(unsigned int d = 2){depth = d;}
private:
    void __add_moves_to_stack(std::stack<std::string> & stk,Game_Man & gm);
    void __add_promote_children_to_stack(std::string basemove, std::stack<std::string> & stk,Game_Man & gm);
};

#endif /* engines.h */