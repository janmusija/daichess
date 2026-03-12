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

int main(int argc, char *argv[]){
    Game g = main_menu();
    bool flagnew = 1;
    std::cout << "type 'help' to show commands.";
    while (true){
        if (flagnew){std::cout << g.display_board(g.get_pl() == 'b');}
        if (g.ai_players.contains(g.get_pl())){
            break;
            flagnew = 1;
            //ai_move(g,g.get_pl());
        } else {
            player_menu(g,g.get_pl());
            flagnew = 1;
        }
    }
    return 0;
}