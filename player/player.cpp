//
// player.cpp
// 2026-03-06
// daichess
//

#include "player/player.h"
#include <iostream>
void main_menu(){ // present player with interface on how to interact with game (e.g. play two-player/solo, play against AI, etc. Further options: rating?)

}

void menu(){ // display menus, etc, using cin and short commands... compare menu payload of cotc 

}

bool player_move(Game & g, int x0, int y0, int x1, int y1, char pl){
    if (!g.withinbounds(x0,y0) || !g.withinbounds(x1,y1)){
        std::cout << "out of bounds!\n";
    } else {
        if (g.board[x0][y0]){
            if (g.legal(x0, y0,x1, y1,pl)){
                g.mov(x0,y0,x1,y1);
                std::cout << "moved successfully.";
                return 1;
            } else {
                std::cout << "you cannot move this piece.\n";
                return 0;
            }
        } else {
            std::cout << "there is no piece here.\n";
            return 0;
        }
    }
}