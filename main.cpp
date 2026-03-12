//
// main.cpp
// 2026-03-05
// daichess
//

#include <iostream>
#include "core/oh_god_why_do_you_not_have_a_hash_for_pairs.h"
#include <unordered_set>
#include "core/piece.h"
#include "core/game.h"
#include "player/player.h"
#include "engine/engines.h"

int main(int argc, char *argv[]){
    Game g = main_menu();
    bool flagnew = 1;
    std::cout << "type 'help' to show commands.";
    {
        std::string gar = std::to_string(g.turnctr);
        g.algebraic_history += gar + ". ";
    }
    random_move ai;
    int i = 0;
    while (true && i < 100){
        if (flagnew){std::cout << g.display_board(g.get_pl() == 'b');}
        if (g.incheck(g.get_pl())){
            std::cout << "check!";
            if (!g.hasmoves(g.get_pl())){
                std::cout << "checkmate!! ";
                if (g.get_pl() == 'b'){
                    std::cout << "white wins!\n";
                } else {
                    std::cout << "black wins!\n";
                }
                std::cout << g.algebraic_history;
                break;
            }
        }
        if (g.ai_players.contains(g.get_pl())){
            ai.e_move(g,g.get_pl());
            flagnew = 1;
        } else {
            player_menu(g,g.get_pl());
            flagnew = 1;
        }
        if (g.fore_pl()){
            std::string gar = std::to_string(g.turnctr);
            g.algebraic_history += "  " + gar + ". ";
        }
    }
    return 0;
}