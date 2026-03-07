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
using intpairmap = std::unordered_map<std::pair<int,int>,int,p_hash>;
#include "betza/notation.h"



class Moveset {
    public:
    intpairmap mleaps; // int -> if -1, nonjumping
    intpairmap cleaps; // int -> if -1, nonjumping
    intpairmap mrides; // int -> length. 0 if infinite. -(i+1) if nonjumping
    intpairmap crides; // int -> length. 0 if infinite. -(i+1) if nonjumping (i.e. -1 is infinite but nonjumping)
    Moveset(std::string bnot);
    Moveset();
    void addmove(std::pair<int,int>,bool isride, int mc, int aux); // mc = 0 -> move and capture. mc = 1 -> move only. mc = -1 -> capture only
};


class Piece {
    public:
    std::string display;
    Moveset moves; 
    std::string betza; // for export
    bool royal;
    char team; // 'b' or 'w';
    // todo: implement `char facing`. can be f (rotated to face +x) r (rotated to face +y) b (-x) or l (-y).
    std::unordered_set<std::string> flag; // e.g. uncastled; ep; not yet moved; 
    Piece(std::string disp, std::string bnot, char tm); // display string, betza notation, team
    void initialize();
};

#endif /* piece.h */