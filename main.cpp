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
    return 0;
}