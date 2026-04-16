//
// game_man.h
// 2026-04-15
// daichess
//

#ifndef game_man_h
#define game_man_h

#include "core/game.h"
#include "core/piece.h"
#include <stack>

class Game_Man{ // manages a game to give undo capabilities
public:
    Game game;
    std::stack<std::unique_ptr<Piece>> piece_stack;
    std::stack<std::string> hist; // moves look like:
    // x0 y0 x1 y1              : basic move. to undo, move piece from x1 y1 to x0 y0
    // x0 y0 x1 y1 - x1 y1      : capture. to undo, just move the piece at x1 y1 to x0 y0, then move the piece on the top of the stack to x1 y1
    // - x1 y1 x0 y0 x1 y1      : promotion. to undo, just move the piece on the top of the stack to x1 y1
    // x0 y0 x1 y1 x2 y2 x3 y3  : the rare double move (e.g. castle). trivial.
    std::string curr_move;
    // return 1
    void add_to_mov(int x0, int y0, int x1, int y1, bool capt);
    void prom(int x, int y);
    void commit_move_to_stack(); // does not make the move, because there is insufficient info

    void pc_to_stack(int x, int y);
    void pc_from_stack(int x, int y);
    bool undo();
    Game_Man(Game & g) : game(g){};
};

#endif /* game_man.h */