//
// player.cpp
// 2026-03-11
// daichess
//

#include "engine/engines.h"

bool Engine::e_move(Game & g, char pl){
    std::pair<std::pair<int,int>,std::pair<int,int>> m = underlying_move(g,pl);
    int x0 = m.first.first; int y0 = m.first.second; int x1 = m.second.first; int y1 = m.second.second;
    if (g.haspiece(m.first.first,m.first.second) && g.withinbounds(m.second.first,m.second.second)){
        int rooklen = -1; int tx = -1; int ty = -1;
        std::string ahr_1 = g.board[x0][y0]->display;
        std::string ahr_2 = algebraic_pos(x0,y0);
        std::string ahr_3 = algebraic_pos(x1,y1);
        bool ahr_4 = (bool)g.board[x1][y1];
        bool cast = g.validcastle(x0,y0,x1,y1,tx,ty,rooklen);
        std::string OO;
        std::string prom_str;
        if (cast){
            for (int i = 0; i< rooklen; i++){
                if (i!= 0){OO += "-O";}
                else {OO += "O";}
            }
            int vx = x1 - x0; int vy = y1 - y0; vx /= 2; vy /= 2;
            g.mov(x0,y0,x1,y1);
            g.mov(tx,ty,x0+vx,y0+vy);
            g.append_to_alg(algebraic_pos(x0,y0),algebraic_pos(x1,y1) + "w/ " + OO);
        } else {
            g.mov(x0,y0,x1,y1);
            if (g.board[x1][y1]->flag.contains("p") && ((pl=='b' && x1 == 0) || (pl == 'w' && x1 == g.board.size()-1))){ // promoters
                std::string gar = e_prom(g,x1,y1, pl);
                g.append_to_alg(algebraic_pos(x0,y0),algebraic_pos(x1,y1) + " =" + gar);
                prom_str = g.board[x1][y1]->display;
            } else{
                g.append_to_alg(x0,y0,x1,y1);
            }
        }
        g.ahr_update(ahr_1,ahr_2,ahr_3,ahr_4,cast,OO,prom_str);
        return true;
    } else {
        return false;
    }
}

std::string Engine::e_prom(Game & g, int x1, int y1, char pl){
    std::string adgadshf = underlying_prom(g,x1,y1,pl);
    char tm = g.board[x1][y1]->team;
    g.placepiece(x1, y1, g.promo[adgadshf].first.first, g.promo[adgadshf].first.second, tm, fc);
    return g.promo[adgadshf].first.second;
}

std::pair<std::pair<int,int>,std::pair<int,int>> random_move::underlying_move(Game & g, char pl){
    std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash> s = g.all_legal_moves(pl);
    return pick_random_member(s,rng);
}

std::string random_move::underlying_prom(Game & g, int x1, int y1, char pl){
    if (g.haspiece(x1,y1)){
        auto it = g.promo.begin();
        unsigned int gar = rng() % g.promo.size();
        for (int i = 0; i<gar; ++i){
            ++it;
        }
        return it->first;
    }
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
    } else if (!all_legal.empty()){
        auto jt = all_legal.begin();
        for (int j = 0; j<(tiebreak % all_legal.size())%32; ++j){
            ++jt;
        }
        ++tiebreak;
        return *jt;
    }
    return std::make_pair(std::make_pair(-1,-1),std::make_pair(-1,-1));
}

std::string CCCP::underlying_prom(Game & g, int x1, int y1, char pl){
    if (g.haspiece(x1,y1)){
        std::string adgadshf = "Q";
        if (!g.promo.contains("Q")){
            auto it = g.promo.begin();
            adgadshf = it->first;
        }
        return adgadshf;
    }
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
