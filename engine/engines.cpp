//
// player.cpp
// 2026-03-11
// daichess
//

#include "engine/engines.h"
#include <sstream>

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

float move_count_heuristic(Piece & p, const int boardsize){
    float f = 1.5;
    f += (float)(p.moves.mleaps.size() + p.moves.cleaps.size() + p.moves.mrides.size() + p.moves.crides.size())/2;

    // bonus from rides. ideally make this a better heuristic.
    for (auto it = p.moves.mrides.begin(); it != p.moves.mrides.end(); it++){
        int xl = it->first.first; int yl = it->first.second; int allowed_dist = it->second;
        float r = std::sqrt((float)(xl*xl + yl*yl));
        if (!(r >= 1)) {continue;}
        float nummoves = ((float)boardsize)/r; if (nummoves > allowed_dist){nummoves = allowed_dist;}
        if (nummoves >= 1){
            f+= 1.5*(1-std::exp((1-nummoves)/7));
        }
    }  


    return f/3;
}  

#define BOARDSIZE_FOR_ALGO 16
#define STALEMATE_PREFERABLE_DISADVANTAGE 10

float quick_heuristic(Game & g, char pl, float & next_p_tot, float & prev_p_tot, std::unordered_map<std::string,float> & val_cache){ // designed for a two player game. pl is the player to move = next_p.
    // evaluates the game for the next player.
    if (!g.hasmoves(pl)) {
        if (g.incheck(pl)){
            next_p_tot = -std::numeric_limits<float>::infinity(); prev_p_tot = std::numeric_limits<float>::infinity(); return next_p_tot;
        } else {
            next_p_tot = -STALEMATE_PREFERABLE_DISADVANTAGE; prev_p_tot = 0; return next_p_tot;
        }
    }
    for (int i = 0; i<g.board.size(); i++){
        for (int j = 0; j < g.board[i].size(); j++){
            if (g.board[i][j]){
                if (!val_cache.contains(g.board[i][j]->betza)){
                    val_cache[g.board[i][j]->betza] = move_count_heuristic(*g.board[i][j],BOARDSIZE_FOR_ALGO);
                }
                if (g.board[i][j]->team == pl){
                    next_p_tot += val_cache[g.board[i][j]->betza];
                } else {
                    prev_p_tot += val_cache[g.board[i][j]->betza];
                }
            }
        }
    }
    return next_p_tot - prev_p_tot;
}

std::pair<std::pair<int,int>,std::pair<int,int>> basic_search_algo::underlying_move(Game & g, char pl){
    Game_Man gm(g);
    unsigned int lev = 0;

    std::stack<std::pair<std::string,unsigned int>> search_tree;

    {// add initial stuff to stack
    std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash> s = gm.game.all_legal_moves(pl);
    for (auto it = s.begin(); it != s.end(); it++){
        std::string str = std::to_string(it->first.first) + " " + std::to_string(it->first.second) + " " + std::to_string(it->second.first) + " " + std::to_string(it->second.second);
        //if // condition for promotion // add separate moves for each individual promotion... yep
        search_tree.push(std::make_pair(str,lev+1));
    }
    }
    std::string CURR_MOVE_SEQ = "";
    std::string CURR_MOVE = "";
    std::unordered_map<std::string,float> move_valuation;
    std::unordered_map<std::string,float> temp_valuations;

    while (!search_tree.empty()){
        // expand. periodically prune. etc
        unsigned int CURR_HT = search_tree.top().second;
        if (lev > CURR_HT){
            // undo move.
            // going down a layer. evaluate by minmax of children in move_valuation.
        }
        CURR_MOVE = search_tree.top().first;
        CURR_MOVE_SEQ += ";" + CURR_MOVE;
        std::istringstream iss_0(CURR_MOVE);

        // parse CURR_MOVE into relevant bits (x0, y0, x1, y1; whether it is castling, potentially promotion) and make move in [gm.game]

        if (CURR_HT == depth){
            // we are at the deepest allowed node. evaluate, add to move_valuation.
        } else if (CURR_HT % prunefreq == 0){
            // do not propagate further yet. evaluate, add to temporary collection [temp_valuations] of current-depth champions.
        } else {
            // continue propagation.
        }
    }






    // cleanup
    while (!search_tree.empty()){
        search_tree.pop();
    }
}
std::string basic_search_algo::underlying_prom(Game & g, int x1, int y1, char pl){
    if (promcache != ""){
        std::string p = promcache; promcache = "";
        return p;
    } else {
        // TK
    }
}