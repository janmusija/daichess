//
// player.cpp
// 2026-03-11
// daichess
//

#include "engine/engines.h"

bool random_move::underlying_move(Game & g, char pl){
    //std::unordered_set<std::pair<int,int>> s = g.legal_moves();
    return 0; // TK
}

bool CCCP::underlying_move(Game & g, char pl){
    return 0; // TK
}

std::pair<int,int> pick_random_member(const std::unordered_set<std::pair<int,int>,p_hash>& options, std::mt19937& rng){
    std::unordered_set<std::pair<int,int>,p_hash>::const_iterator it = options.begin();
    unsigned int gar = rng() % options.size();
    for (int i = 0; i<gar; ++i){
        ++it;
    }
    return *it;
}