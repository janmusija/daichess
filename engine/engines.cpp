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
    return pick_random_member(s,rng);
}

std::pair<std::pair<int,int>,std::pair<int,int>> CCCP::underlying_move(Game & g, char pl){
    std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash> all_legal = g.all_legal_moves(pl); // tk
    std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash> checks;
    std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash> captures;
    std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash> push;
    for (auto it = all_legal.begin(); it != all_legal.end(); it++){
        Game h(g);
        h.mov(*it);
        h.fore_pl();
        if (h.incheck(h.get_pl())){
            if (!h.hasmoves(h.get_pl())){
                return *it;
            } else {
                checks.insert(*it);
            }
        }
        if (g.board[it->second.first][it->second.second]){
            captures.insert(*it);
        }
        if ((pl == 'w' && (it->second.first > it->first.first)) || (pl == 'b' && (it->second.first < it->first.first))){
            push.insert(*it);
        }
    }
    if (!checks.empty()){
        auto jt = checks.begin();
        for (int j = 0; j<(tiebreak % checks.size())%32; ++j){
            ++jt;
        }
        ++tiebreak;
        return *jt;
    } else if (!captures.empty()){
        auto jt = captures.begin();
        for (int j = 0; j<(tiebreak % captures.size())%32; ++j){
            ++jt;
        }
        ++tiebreak;
        return *jt;
    } else if (!push.empty()){
        auto jt = push.begin();
        for (int j = 0; j<(tiebreak % push.size())%32; ++j){
            ++jt;
        }
        ++tiebreak;
        return *jt;
    }
    return std::make_pair(std::make_pair(-1,-1),std::make_pair(-1,-1));
}

std::pair<int,int> pick_random_member(const std::unordered_set<std::pair<int,int>,p_hash>& options, std::mt19937& rng){ // returns (-1,-1) on fail
    if (options.empty()){
        return std::make_pair(-1,-1);
    }
    std::unordered_set<std::pair<int,int>,p_hash>::const_iterator it = options.begin();
    unsigned int gar = rng() % options.size();
    for (int i = 0; i<gar; ++i){
        ++it;
    }
    return *it;
}

std::pair<std::pair<int,int>,std::pair<int,int>> pick_random_member(const std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash>& options, std::mt19937& rng){ // returns ((-1,-1),(-1,-1)) on fail
    if (options.empty()){
        return std::make_pair(std::make_pair(-1,-1),std::make_pair(-1,-1));
    }
    std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash>::const_iterator it = options.begin(); 
    unsigned int gar = rng() % options.size();
    for (int i = 0; i<gar; ++i){
        ++it;
    }
    return *it;
}
