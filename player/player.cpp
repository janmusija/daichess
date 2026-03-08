//
// player.cpp
// 2026-03-06
// daichess
//

#include "player/player.h"
#include <iostream>
void main_menu(Game & g){ // present player with interface on how to interact with game (e.g. play two-player/solo, play against AI, etc. Further options: rating?)
    std::cout << "Would you like to play a new game ('new') or load a preexisting game?";
    std::string resp;
    std::cin >> resp;
    // TK
}

#define debug_menu 1

void player_menu(Game & g, char pteam){ // display menus, etc, using cin and short commands... compare menu payload of cotc 
    // player turn
    bool turn = 1;
    while (turn){
        std::string resp;
        std::cin >> resp;
        if (resp == "help") {
            std::cout << "test";
        }
        else if (resp == "show") {
            std::cout << g.display_board(pteam == 'b');
        }
        else if (resp == "moves" || resp == "mvs") {
            std::string src; std::cin >> src;
            std::cout << g.display_moves(src) << "\n";
        }
        else if (resp == "moveset"){
            // display moves a piece COULD make
            std::string src; std::cin >> src;
            int x = pos_algebraic(src).first;
            int y = pos_algebraic(src).second;
            if (g.haspiece(x,y)){
                std::cout << "movement leaps:\n";
                for (auto it = g.board[x][y]->moves.mleaps.begin(); it!= g.board[x][y]->moves.mleaps.end(); it++){
                    std::cout << "(" << it->first.first << ", " << it -> first.second << "), ";
                }
                std::cout << "capture leaps:\n";
                for (auto it = g.board[x][y]->moves.cleaps.begin(); it!= g.board[x][y]->moves.cleaps.end(); it++){
                    std::cout << "(" << it->first.first << ", " << it -> first.second << "), ";
                }
                std::cout << "movement rides\n";
                for (auto it = g.board[x][y]->moves.mrides.begin(); it!= g.board[x][y]->moves.mrides.end(); it++){
                    std::cout << "(" << it->first.first << ", " << it -> first.second; 
                    std::cout << "), ";
                }
                std::cout << "capture rides:\n";
                for (auto it = g.board[x][y]->moves.crides.begin(); it!= g.board[x][y]->moves.crides.end(); it++){
                    std::cout << "(" << it->first.first << ", " << it -> first.second;
                    std::cout << "), ";
                }
                std::cout << "\n";
            }
        }

        #if debug_menu == 1
        else if (resp == "dmove" || resp == "dmv"){
            std::string src; std::string targ;
            std::cin >> src; std::cin >> targ;
            std::pair<int,int> xy0 = pos_algebraic(src);
            std::pair<int,int> xy1 = pos_algebraic(targ);
            g.mov(xy0.first,xy0.second,xy1.first,xy1.second);
        }
        #endif

        else if (resp == "move" || resp == "mv"){
            std::string src; std::string targ;
            std::cin >> src; std::cin >> targ;
            std::pair<int,int> xy0 = pos_algebraic(src);
            std::pair<int,int> xy1 = pos_algebraic(targ);
            if (player_move(g,xy0.first,xy0.second,xy1.first,xy1.second,pteam)){
                turn = 0;
                std::cout << "show board? (y/n):";
                std::cin >> resp;
                if (resp != "n"){
                    std::cout << g.display_board(pteam == 'b');
                }
            }
        }
    }
}

bool player_move(Game & g, int x0, int y0, int x1, int y1, char pl){
    if (!g.withinbounds(x0,y0) || !g.withinbounds(x1,y1)){
        std::cout << "out of bounds!\n";
        return 0;
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