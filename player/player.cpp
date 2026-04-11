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
Game main_menu(std::unordered_map<char,int> & ai_id_map){ // present player with interface on how to interact with game (e.g. play two-player/solo, play against AI, etc. Further options: rating?)
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
        bool both_ai = 0;
        while (needresp){
            std::cout << "Play against another person opponent ('p', 'person', 'h', 'human') or against an engine ('a', 'ai', 'e', 'engine)? or watch two bots ('2'): ";
            std::cin >> resp;    
            if (resp == "h" || resp == "human" || resp == "p" || resp == "person" || resp == "a" || resp == "ai" || resp == "e" || resp == "engine" || resp == "2"){
                needresp = 0;
                if (resp == "a" || resp == "ai" || resp == "e" || resp == "engine"){
                    ai_opp = 1;
                }
                if (resp == "2"){
                    both_ai = 1;
                }
            }
        }
        char ai_pl = 'w';
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
                    ai_pl = 'w';
                } else {
                    ai_pl = 'b';
                }
            }
            else if (resp == "b"){
                ai_pl = 'w';
            } else {
                ai_pl = 'b';
            }
        }
        if (both_ai || ai_opp){
            std::cout << "ai ids are integers from 0 to 1 (inclusive).\n"; //document further later
        }
        if (both_ai){
            std::cout << "Enter id for ai playing white: ";
            int r = 0;
            std::cin >> r;
            ai_id_map['w'] = r;
            std::cout << "Enter id for ai playing black: ";
            r = 0;
            std::cin >> r;
            ai_id_map['b'] = r;
        }
        else if (ai_opp){
            std::cout << "Enter id for ai opponent: ";
            int r = 0;
            std::cin >> r;
            ai_id_map[ai_pl] = r;
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
            std::cout << "Type 'dmv' to forcibly move a piece regardless of legality. This does not pass your turn. (DEBUG MENU)\n";
            std::cout << "Type 'dset' to change or set a piece. Enter position, Betza notation, associated player (e.g. w), and then a display string. (DEBUG MENU)\n";
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
        }/*
        else if (resp == "ddel" || resp == "delete"){
            std::string targ;
        }*/
        else if (resp == "dset" || resp == "ds"){
            std::string targ; std::string betza; std::string team;
            std::cin >> targ; std::cin >> betza; std::cin >> team;
            std::pair<int,int> xy0 = pos_algebraic(targ);
            g.placepiece(xy0.first, xy0.second, betza, team[0]);
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

std::string player_promote(Game & g, int x1, int y1, char pteam){
    std::cout << "You are in the promotion menu for the piece at " << algebraic_pos(x1,y1) << ". Type 'help' for help.\n";
    bool needs_prom = 1;
    while (needs_prom){
        std::string resp;
        std::cin >> resp;
        if (resp == "help") {
            #if debug_menu
            std::cout << "DEBUG MENU ACTIVE!\n";
            #endif
            std::cout << "type 'help' for this menu.\n";
            std::cout << "Type 'show' to show the board.\n";
            std::cout << "Type 'opt' to show the promotion options (betza notation).\n";
            std::cout << "Type 'p' to promote the piece at" << algebraic_pos(x1,y1) << "\n";
            //std::cout << "Type 'moveset' and a position to see all the moves a piece can make. 'leaps' refer to the simplest, most direct moves a piece can make; 'rides' are moves whereby a piece may repeatedly leap in the same direction across empty space. The convention is that the first coordinate is units forward and the second is units rightward.\n";
            #if debug_menu
            std::cout << "Type 'dpass' to not promote. (DEBUG MENU)\n";
            #endif
            std::cout << "Type 'history' to see the moves of this game so far.\n";
        } else if (resp == "show"){
            std::cout << g.display_board(pteam == 'b');
        } else if (resp == "opt"){
            bool firs = 1;
            for (auto it = g.promo.begin(); it!= g.promo.end(); it++){
                if (it->second.second){
                    if (firs) {firs =0;} else {std::cout << ", ";}
                    std::cout << it->first;
                }
            }
            std::cout << "\n";
        } else if (resp == "p"){
            std::string adhsdjf;
            std::cin >> adhsdjf;
            if (g.promo.contains(adhsdjf)){
                needs_prom = 0;
                if (g.haspiece(x1,y1)){
                    char tm = g.board[x1][y1]->team;
                    g.placepiece(x1, y1, g.promo[adhsdjf].first.first, g.promo[adhsdjf].first.second, tm);
                    return g.promo[adhsdjf].first.second;
                }
            } else {
                std::cout << "not a valid promotion!\n";
            }
        }
        #if debug_menu
        else if (resp == "dpass"){
            needs_prom = 0;
        }
        #endif
        else if (resp == "history"){
            std:: cout << "\n" << g.algebraic_history << "\n";
        }
    }
    return "";
}

bool player_move(Game & g, int x0, int y0, int x1, int y1, char pl){
    if (!g.withinbounds(x0,y0) || !g.withinbounds(x1,y1)){
        std::cout << "out of bounds!\n";
        return 0;
    } else {
        if (g.board[x0][y0]){
            if (g.legal(x0,y0,x1,y1,pl)){
                int rooklen = -1; int tx = -1; int ty = -1; 
                if (g.validcastle(x0,y0,x1,y1,tx,ty,rooklen)){
                    std::string OO;
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
                        std::string gar = player_promote(g,x1,y1, pl);
                        g.append_to_alg(algebraic_pos(x0,y0),algebraic_pos(x1,y1) + " =" + gar);
                    } else{
                        g.append_to_alg(x0,y0,x1,y1);
                    }
                }
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