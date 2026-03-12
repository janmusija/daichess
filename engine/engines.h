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

// tk

class Engine {
public:
    virtual bool underlying_move(Game & g, char pl); // make a legal move in a given position (technically you could make an engine that cheats, I guess). return 1 if successful; otherwise forfeit.
    bool make_move(Game & g, char pl); // wrapped with miscellaneous details to ensure the move is processed properly
};

class random_move : public Engine {
    /*
    makes a random legal move.
    */
public:
    bool underlying_move(Game & g, char pl);
};
std::pair<int,int> pick_random_member(const std::unordered_set<std::pair<int,int>,p_hash>& options, std::mt19937& rng);
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
    bool underlying_move(Game & g, char pl);
};

#endif /* engines.h */