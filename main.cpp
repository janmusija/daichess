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
    Game g = main_menu(ai_id_map);
    bool flagnew = 1;
    std::cout << "type 'help' to show commands.\n";
    {
        std::string gar = std::to_string(g.turnctr);
        g.algebraic_history += gar + ". ";
    }

    // can be changed. more robust tournament support later.
    random_move ai_0;
    CCCP ai_1;
    basic_search_algo ai_2(2);
    basic_search_algo ai_3(3);

    int i = 0;
    char res = ' ';
    while (true){
        ++i;
        if (res != ' '){
            if (res == 'w'){
                std::cout << "white resigns.\n";
            }
            else if (res == 'b'){
                std::cout << "black resigns.\n";
            }
            std::cout << g.display_board(0);
            std::cout << g.algebraic_history;
            break;
        }
        if (g.incheck(g.get_pl())){
            if (!g.hasmoves(g.get_pl())){
                std::cout << "checkmate!!\n";
                if (g.get_pl() == 'b'){
                    std::cout << "white wins!\n";
                } else {
                    std::cout << "black wins!\n";
                }
                std::cout << g.display_board(0);
                std::cout << g.algebraic_history_real;
                break;
            } else {
                std::cout << "check!\n"; // I should be adding these to the notation I guess
            }
        } else {
            if (!g.hasmoves(g.get_pl()) || i > 1000){
                std::cout << "stalemate...\n";
                std::cout << g.display_board(0);
                std::cout << g.algebraic_history_real;
                break;
            }
        }
        if (ai_id_map.contains(g.get_pl())){
            #define spam 1
            #if spam
            if (flagnew && g.get_pl() == 'w'){std::cout << g.display_board(g.get_pl() == 'b');}
            #endif
            bool played_successfully = 0;
            res = g.get_pl();
            switch (ai_id_map[g.get_pl()]){
                case 0:
                played_successfully = ai_0.e_move(g,g.get_pl()); break;
                case 1:
                played_successfully = ai_1.e_move(g,g.get_pl()); break;
                case 2:
                played_successfully = ai_2.e_move(g,g.get_pl()); break;
                case 3:
                played_successfully = ai_3.e_move(g,g.get_pl()); break;
                default:
                played_successfully = ai_0.e_move(g,g.get_pl()); break;
            }
            if (played_successfully) {res = ' ';}
            flagnew = 1;
        } else {
            if (flagnew){std::cout << g.display_board(g.get_pl() == 'b');}
            player_menu(g,g.get_pl());
            flagnew = 1;
        }
        if (g.fore_pl()){
            std::string gar = std::to_string(g.turnctr);
            g.algebraic_history += "  " + gar + ". ";
        }
    }
    std::cout << "\n" << g.algebraic_history_real << "\n";
    return 0;
}