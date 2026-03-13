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
    std::unordered_map<char,int> ai_id_map;
    Game g = main_menu();
    bool flagnew = 1;
    std::cout << "type 'help' to show commands.";
    {
        std::string gar = std::to_string(g.turnctr);
        g.algebraic_history += gar + ". ";
    }

    // can be changed. more robust tournament support later.
    random_move ai_0;
    CCCP ai_1;
    ai_id_map['w'] = 0; // todo: get rid of Game::ai_players and replace by adding ai_id_map as a reference passed to main_menu() which can be configured frely
    ai_id_map['b'] = 1;

    int i = 0;
    while (true){
        if (flagnew){std::cout << g.display_board(g.get_pl() == 'b');}
        if (g.incheck(g.get_pl())){
            if (!g.hasmoves(g.get_pl())){
                std::cout << "checkmate!! ";
                if (g.get_pl() == 'b'){
                    std::cout << "white wins!\n";
                } else {
                    std::cout << "black wins!\n";
                }
                std::cout << g.algebraic_history;
                break;
            } else {
                std::cout << "check!";
            }
        }
        if (g.ai_players.contains(g.get_pl())){
            if (ai_id_map.contains(g.get_pl())){
                switch (ai_id_map[g.get_pl()]){
                    case 0:
                    ai_0.e_move(g,g.get_pl()); break;
                    case 1:
                    ai_1.e_move(g,g.get_pl()); break;
                }
            } else {
                ai_0.e_move(g,g.get_pl());
            }
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
    std::cout << "\n" << g.algebraic_history << "\n";
    return 0;
}