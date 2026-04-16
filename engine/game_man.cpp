//
// game_man.cpp
// 2026-04-15
// daichess
//

#include "engine/game_man.h"
#include <stack>
#include <string>
#include <sstream>

void Game_Man::add_to_mov(int x0, int y0, int x1, int y1, bool capt){
    std::string s;
    if (capt){
        s+= "- " + std::to_string(x1) + std::to_string(y1) + " ";    
    }
    s += std::to_string(x0) + " " + std::to_string(y0) + " " + std::to_string(x1) + " " + std::to_string(y1);
    if (!curr_move.empty()){
        s += " ";
    }
    curr_move = s + curr_move;
}

void Game_Man::prom(int x, int y){
    std::string s;
    s += "- "+ std::to_string(x) + " " + std::to_string(y);
    if (!curr_move.empty()){
        s += " ";
    }
    curr_move = s + curr_move;
}

void Game_Man::commit_move_to_stack(){
    hist.push(curr_move);
    curr_move = "";
}

void Game_Man::pc_to_stack(int x, int y){
    piece_stack.push(nullptr);
    std::swap(game.board[x][y],piece_stack.top());
}

void Game_Man::pc_from_stack(int x, int y){
    std::swap(game.board[x][y],piece_stack.top());
    piece_stack.pop();
}

bool Game_Man::undo(){
    if (hist.empty()){
        return false;
    }
    std::istringstream iss_0(hist.top());
    std::string s_1;
    while (getline(iss_0, s_1,' ')){
        if (s_1 == "-"){
            // promote / capature
            getline(iss_0, s_1,' ');
            int x = std::atoi(s_1.c_str());
            getline(iss_0, s_1,' ');
            int y = std::atoi(s_1.c_str());
            pc_from_stack(x,y);
        } else {
            int x0 = std::atoi(s_1.c_str());
            getline(iss_0, s_1,' ');
            int y0 = std::atoi(s_1.c_str());
            getline(iss_0, s_1,' ');
            int x1 = std::atoi(s_1.c_str());
            getline(iss_0, s_1,' ');
            int y1 = std::atoi(s_1.c_str());
            std::swap(game.board[x0][y0],game.board[x1][y1]);
        }
    }
    // undo move
    hist.pop();
    game.back_pl();
    return true;
}

void Game_Man::execute_move(std::string __mov, std::string & __PROM){ // parse out a move and add it to the history. This is a different syntax from history,
    // differing in that instead of - x1 y1 for captures and promotions there is only = [string] for promotions [and it is implicitly at the last position]
    std::istringstream iss_0(__mov);
    std::string s_1;
    std::string new_hist = "";
    int x1 = -1; int y1 = -1;
    char pf = (game.get_pl()=='b')?'b':'f'; // not really a robust way to check facing
    while (getline(iss_0, s_1,' ')){
        if (s_1 == "="){ // promo
            std::string hist_chunk = "- " + std::to_string(x1) + " " + std::to_string(y1);
            getline(iss_0, __PROM,' '); // __PROM is now the promo string
            pc_to_stack(x1,y1);
            game.placepiece(x1, y1, game.promo[__PROM].first.first, game.promo[__PROM].first.second, game.get_pl(),pf);

            if (!new_hist.empty()){
                hist_chunk += " ";
            }
            new_hist = hist_chunk + new_hist;
        } else { // move
            std::string hist_chunk = s_1;
            int x0 = std::atoi(s_1.c_str());
            getline(iss_0, s_1,' '); hist_chunk += " " + s_1;
            int y0 = std::atoi(s_1.c_str());
            getline(iss_0, s_1,' '); std::string _xy1 = " " + s_1;
            x1 = std::atoi(s_1.c_str());
            getline(iss_0, s_1,' '); _xy1 += " " + s_1;
            y1 = std::atoi(s_1.c_str());
            hist_chunk += _xy1;
            if (game.board[x1][y1]){
                hist_chunk += " -" + _xy1;
                pc_to_stack(x1,y1);
            }
            std::swap(game.board[x0][y0],game.board[x1][y1]);

            if (!new_hist.empty()){
                hist_chunk += " ";
            }
            new_hist = hist_chunk + new_hist;
        }
    }
    hist.push(new_hist);
    game.fore_pl();
}
void Game_Man::execute_moves(std::string __movs, std::string & __PROM){ // parse out as sequence of moves and run execute_move repeatedly
    std::istringstream iss_0(__movs);
    bool b = 1;
    std::string trash;
    std::string s_1;
    while (getline(iss_0, s_1,';')){
        if (b){b = 0;
        execute_move(s_1,__PROM);} else {
        execute_move(s_1,__PROM);}
    }
}