//
// piece.h
// 2026-03-05
// daichess
//

// API for pieces

// I realize that I am again implementing a turn based strategy game

#ifndef piece_h
#define piece_h

#include <string>
#include "core/oh_god_why_do_you_not_have_a_hash_for_pairs.h"
#include <unordered_set>
#include <unordered_map>
#include "betza/notation.h"

class Moveset {
    public:
    std::unordered_map<std::pair<int,int>,int> mleaps; // int -> if -1, nonjumping
    std::unordered_map<std::pair<int,int>,int> cleaps; // int -> if -1, nonjumping
    std::unordered_map<std::pair<int,int>,int> mrides; // int -> length. 0 if infinite. -(i+1) if nonjumping
    std::unordered_map<std::pair<int,int>,int> crides; // int -> length. 0 if infinite. -(i+1) if nonjumping (i.e. -1 is infinite but nonjumping)
    Moveset(std::string bnot);
    void addmove(std::pair<int,int>,bool isride, int mc, int aux); // mc = 0 -> move and capture. mc = 1 -> move only. mc = -1 -> capture only
}


class Piece {
    public:
    std::string display;
    Moveset moves; 
    bool royal;
    char team; // 'b' or 'w';
    std::unordered_set<std::string> flag; // e.g. uncastled; ep; not yet moved; 
    Piece(std::string disp, std::string bnot, char tm);
    void initialize();
};

#endif /* piece.h */