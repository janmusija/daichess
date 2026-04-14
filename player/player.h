//
// player.h
// 2026-03-06
// daichess
//

#ifndef player_h
#define player_h
#include <iostream>
#include "core/game.h"

Game main_menu(std::unordered_map<char,int> & ai_id_map); // present player with interface on how to interact with game (e.g. play two-player/solo, play against AI, etc. Further options: rating?)

void player_menu(Game & g, char pteam); // display menus, etc, using cin and short commands... compare menu payload of cotc 

inline void show_board(Game & g) {
    std::cout << g.display_board(0);
}

inline void get_moves(Game & g, int x, int y){
    std::cout << algebraic_pos(x,y) << ": " << g.display_moves(x,y) << "\n";
}

bool player_move(Game & g, int x0, int y0, int x1, int y1, char pl);
std::string player_promote(Game & g, int x1, int y1, char pteam, char pf);

inline void get_algebraic_history(const Game & g){
    std::cout << g.algebraic_history << "\n";
}


#endif /* player.h */