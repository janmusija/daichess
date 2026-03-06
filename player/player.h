//
// player.h
// 2026-03-06
// daichess
//

#ifndef player_h
#define player_h
#include <iostream>
#include "core/game.h"

void main_menu(){
    // present player with interface on how to interact with game (e.g. play two-player/solo, play against AI, etc. Further options: rating?)
}

void menu(){
    // display menus, etc, using cin and short commands... compare menu payload of cotc 
}

void show_board(Game & g){
    std::cout << g.display_board(0);
}

void get_moves(Game & g, int x, int y){
    std::cout << algebraic_pos(x,y) << ": " << g.display_moves(x,y) << "\n";
}

void player_move(Game & g, int x0, int y0, int x1, int y1,char pl){
    if (!g.withinbounds(x0,y0) || !g.withinbounds(x1,y1)){
        std::cout << "out of bounds!\n";
    } else {
        if (g.board[x0][y0]){
            if (g.accessible_moves(x0, y0, pl).contains(std::make_pair(x1,y1))){
                g.mov(x0,y0,x1,y1);
                std::cout << "moved successfully. display board?\n";
                // cin here
            } else {
                std::cout << "you cannot move this piece.\n";
            }
        } else {
            std::cout << "there is no piece here.\n";
        }
    }
}

void get_algebraic_history(const Game & g){
    std::cout << g.algebraic_history << "\n";
}


#endif /* player.h */