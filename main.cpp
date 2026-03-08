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
    player_move(g,1,2,4,1,'w');
    player_move(g,1,0,1,2,'w');
    player_move(g,1,2,1,1,'w');
    player_move(g,2,3,4,4,'w');
    player_move(g,1,1,1,3,'w');
    player_move(g,1,3,1,0,'w');
    std::cout << g.display_board(0); 
    std::cout << algebraic_pos(1,0) << " has access to " << algebraic_pos(1,1) << ": ";
    std::cout << g.accesses(1,0,1,1) << "\n";
    std::cout << "white has moves: " << g.hasmoves('w') << "\n"; 
    player_menu(g,'w');
    return 0;
}