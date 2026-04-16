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
}