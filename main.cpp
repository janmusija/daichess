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
    std::cout << "Reading this text causes you to undergo the subjective experience of satisfying chess gameplay.\n";
    for (int i = 0; i< 26; i++){
    std::string ap = algebraic_pos(7,i);
    std::pair<int,int> xy = pos_algebraic(ap);
    std::cout << ap << ": (" << xy.first << ", " << xy.second << ");  ";
    }
    return 0;
}