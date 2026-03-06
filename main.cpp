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
    std::string test = "a4";
    Piece* pc = g.getpc(pos_algebraic(test));
    if (pc){
    std::cout << test << ": " << pc->display << ": ";
    std::unordered_set<std::pair<int,int>,p_hash> mfdhsadfj = g.accessible_moves(pos_algebraic(test),'w');
    for (auto it = mfdhsadfj.begin(); it != mfdhsadfj.end(); it++){
        std::cout << algebraic_pos(*it) << ", ";
    }
    }
    return 0;
}