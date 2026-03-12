//
// player.cpp
// 2026-03-11
// daichess
//

#include "engine/engines.h"

bool Engine::e_move(Game & g, char pl){
    std::pair<std::pair<int,int>,std::pair<int,int>> m = underlying_move(g,pl);
    if (g.haspiece(m.first.first,m.first.second) && g.withinbounds(m.second.first,m.second.second)){
        g.mov(m.first.first,m.first.second,m.second.first,m.second.second);
        g.append_to_alg(m.first.first,m.first.second,m.second.first,m.second.second);
        return true;
    } else {
        return false;
    }
}

std::pair<std::pair<int,int>,std::pair<int,int>> random_move::underlying_move(Game & g, char pl){
    std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash> s = g.all_legal_moves(pl);
    std::mt19937 rng(time(nullptr));
    return pick_random_member(s,rng);
}

std::pair<std::pair<int,int>,std::pair<int,int>> CCCP::underlying_move(Game & g, char pl){
    std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash> s = g.all_legal_moves(pl); // tk
    std::mt19937 rng(time(nullptr));
    return pick_random_member(s,rng);
}

std::pair<int,int> pick_random_member(const std::unordered_set<std::pair<int,int>,p_hash>& options, std::mt19937& rng){
    std::unordered_set<std::pair<int,int>,p_hash>::const_iterator it = options.begin();
    unsigned int gar = rng() % options.size();
    for (int i = 0; i<gar; ++i){
        ++it;
    }
    return *it;
}

std::pair<std::pair<int,int>,std::pair<int,int>> pick_random_member(const std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash>& options, std::mt19937& rng){
    std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash>::const_iterator it = options.begin();
    unsigned int gar = rng() % options.size();
    for (int i = 0; i<gar; ++i){
        ++it;
    }
    return *it;
}
