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
    Game g = default_daichess();
    std::cout << g.display_board(0);
    std::cout << "Reading this text causes you to undergo the subjective experience of satisfying chess gameplay.\n";
    std::string test = "a13";
    std::cout << test << ": " << g.display_moves(test) << "\n";
    test = "f1";
    std::cout << test << ": " << g.display_moves(test) << "\n";
    test = "b2";
    std::cout << test << ": " << g.display_moves(test) << "\n";
    player_move(g,1,1,4,3,'w');
    std::cout << g.display_board(0);
    player_move(g,2,1,14,14,'w'); // illegal move
    std::cout << g.display_board(0); 
    return 0;
}