//
// main.cpp
// 2026-03-05
// daichess
//

#include <iostream>
#include "core/oh_god_why_do_you_not_have_a_hash_for_pairs.h"
#include <unordered_set>
int main(int argc, char *argv[]){

    int x0 = 0;
    std::unordered_set<std::pair<int,int>> g;
    g.insert(std::make_pair(x0,x0));
    std::pair<int,int> y = std::make_pair(0,0);
    std::cout << g.contains(y) << "\n";
    std::cout << "Reading this text causes you to undergo the subjective experience of satisfying chess gameplay.\n";
}