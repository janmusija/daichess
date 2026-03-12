//
// player.cpp
// 2026-03-06
// daichess
//

#include "player/player.h"
#include <iostream>
#include <random>
#include <ctime>
#include <string>
Game main_menu(){ // present player with interface on how to interact with game (e.g. play two-player/solo, play against AI, etc. Further options: rating?)
    bool needresp = 1;
    std::string resp;
    while (needresp){
    std::cout << "Would you like to play a new game ('new') or load a preexisting game ('load'): ";
    std::cin >> resp;    
        if (resp == "new" || resp == "load"){
            needresp = 0;
        }
    }
    Game g = default_daichess(); // more general newgame generation TK
    if (resp == "load"){
        // TK
    } else { // new game

        needresp = 1;
        bool ai_opp = 0;
        while (needresp){
            std::cout << "Play against another person opponent ('p', 'person', 'h', 'human') or against an engine ('a', 'ai', 'e', 'engine): ";
            std::cin >> resp;    
            if (resp == "h" || resp == "human" || resp == "p" || resp == "person" || resp == "a" || resp == "ai" || resp == "e" || resp == "engine"){
                needresp = 0;
                if (resp == "a" || resp == "ai" || resp == "e" || resp == "engine"){
                    ai_opp = 1;
                }
            }
        }
        if (ai_opp){
            needresp = 1;
            while (needresp){
                std::cout << "choose your side ('w'/'b'/'r' for white/black/random): ";
                std::cin >> resp;    
                if (resp == "b" || resp == "w" || resp == "r"){
                    needresp = 0;
                }
            }
            if (resp != "b" && resp != "w"){
                std::mt19937 mt(time(nullptr));
                if (mt()%2 == 0) {
                    g.ai_players.insert('w');
                } else {
                    g.ai_players.insert('b');
                }
            }
            else if (resp == "b"){
                g.ai_players.insert('w');
            } else {
                g.ai_players.insert('b');
            }
        }
    }
    return g;
}

#define debug_menu 1

void player_menu(Game & g, char pteam){ // display menus, etc, using cin and short commands... compare menu payload of cotc 
    // player turn
    bool turn = 1;
    while (turn){
        std::string resp;
        std::cin >> resp;
        if (resp == "help") {
            #if debug_menu
            std::cout << "DEBUG MENU ACTIVE!\n";
            #endif
            std::cout << "type 'help' for this menu.\n";
            std::cout << "Type 'show' to show the board.\n";
            std::cout << "Type 'moves' or 'mvs' followed by the notation for some position on the board to show the available moves for a given piece. (including one you do not control!)\n";
            std::cout << "Type 'moveset' and a position to see all the moves a piece can make. 'leaps' refer to the simplest, most direct moves a piece can make; 'rides' are moves whereby a piece may repeatedly leap in the same direction across empty space. The convention is that the first coordinate is units forward and the second is units rightward.\n";
            std::cout << "Type 'move' or 'mv' followed by the notations for two positions to move a piece from one position to another\n";
            #if debug_menu
            std::cout << "Type 'dpass' to pass your turn. (DEBUG MENU)\n";
            std::cout << "Type 'dmv' to forcibly move a piece regardless of legality. (DEBUG MENU)\n";
            #endif
            std::cout << "Type 'history' to see the moves of this game so far.\n";
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
                bool flag = 0;
                for (auto it = g.board[x][y]->moves.mleaps.begin(); it!= g.board[x][y]->moves.mleaps.end(); it++){
                    if (flag){std::cout << ", ";} else {flag = 1;}
                    std::cout << "(" << it->first.first << ", " << it -> first.second << ")";
                }
                std::cout << "\ncapture leaps:\n"; flag = 0;
                for (auto it = g.board[x][y]->moves.cleaps.begin(); it!= g.board[x][y]->moves.cleaps.end(); it++){
                    if (flag){std::cout << ", ";} else {flag = 1;}
                    std::cout << "(" << it->first.first << ", " << it -> first.second << ")";
                }
                std::cout << "\nmovement rides\n"; flag = 0;
                for (auto it = g.board[x][y]->moves.mrides.begin(); it!= g.board[x][y]->moves.mrides.end(); it++){
                    if (flag){std::cout << ", ";} else {flag = 1;}
                    std::cout << "(" << it->first.first << ", " << it -> first.second << ")";
                    int aux = it->second;
                    if (aux < 0){
                        aux = -1-aux;
                    }
                    if (aux > 0){
                        std::cout << " length " << aux;
                    }
                }
                std::cout << "\ncapture rides:\n"; flag = 0;
                for (auto it = g.board[x][y]->moves.crides.begin(); it!= g.board[x][y]->moves.crides.end(); it++){
                    if (flag){std::cout << ", ";} else {flag = 1;}
                    std::cout << "(" << it->first.first << ", " << it -> first.second << ")";
                    int aux = it->second;
                    if (aux < 0){
                        aux = -1-aux;
                    }
                    if (aux > 0){
                        std::cout << " length " << aux;
                    }
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
        else if (resp == "dpass") {
            turn = 0;
        }
        #endif

        else if (resp == "move" || resp == "mv"){
            std::string src; std::string targ;
            std::cin >> src; std::cin >> targ;
            std::pair<int,int> xy0 = pos_algebraic(src);
            std::pair<int,int> xy1 = pos_algebraic(targ);
            if (player_move(g,xy0.first,xy0.second,xy1.first,xy1.second,pteam)){
                turn = 0;
                std::cout << "show board? (y/n): ";
                std::cin >> resp;
                if (resp != "n"){
                    std::cout << g.display_board(pteam == 'b');
                }
            }
        }
        else if (resp == "history" || resp == "hist"){
            std:: cout << "\n" << g.algebraic_history << "\n";
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
                g.append_to_alg(x0,y0,x1,y1);
                std::cout << "moved successfully.\n";
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