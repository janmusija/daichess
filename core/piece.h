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
    Moveset(std::string bnot,bool initonly = 0);
    Moveset();
    void addmove(std::pair<int,int>,bool isride, int mc, int aux); // mc = 0 -> move and capture. mc = 1 -> move only. mc = -1 -> capture only
};


class Piece {
    public:
    std::string display;
    Moveset moves;
    Moveset init_only_moves; // these are deleted from Moves after the first move
    std::string betza; // for export
    bool royal;
    char team; // 'b' or 'w';
    std::unordered_set<std::string> flag; // e.g. uncastled; ep; not yet moved; 
    Piece(std::string disp, std::string bnot, char tm, char fc); // display string, betza notation, team, facing
    void initialize();
    Piece(char tm, bool royal); // dummy piece
    void prune_init_moves(); //get rid of init_only_moves

    char facing; 
    /* the move (2,1) is:

       y|f
      l | c    
      --+--
      h | r
       b|x
    
       f = ( x, y)
       y = ( x,-y)
       x = (-x, y)
       l = ( y,-x)
       r = (-y, x)
       c = ( y, x)
       h = (-y,-x)
       b = (-x,-y)
    */
    bool facing_RtA(const int x, const int y, int & _x_, int & _y_); // relative to absolute
    bool facing_AtR(const int x, const int y, int & _x_, int & _y_); // absolute to relative
};

#endif /* piece.h */