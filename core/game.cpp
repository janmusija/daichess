//
// game.cpp
// 2026-034-05
// daichess
//

#include "core/game.h"
#include <string>


#define DISPLAYLEN 3

Game::Game(int x, int y){
    board.clear();
    players = {'w','b'};
    width = y;
    height = x;
    for (int i = 0; i<x; i++){
        board.emplace_back(y); //yes, this creates a vector of y many nullpointers, *obviously*
    }
}

Game::Game(int x, int y, std::vector<char>&& p){
    board.clear();
    players = p;
    width = y;
    height = x;
    for (int i = 0; i<x; i++){
        board.emplace_back(y); 
    }
}

bool Game::placepiece(int x, int y, std::string betza, char tm){
    std::string b = betza;
    b.resize(DISPLAYLEN,' ');
    return placepiece(x,y,b,betza,tm);
}

#include <iostream>
bool Game::placepiece(int x, int y, std::string disp, std::string betza, char tm){
    if (betza == ""){return 0;}
    else if ((int) board.size() <= x || x < 0 || (int) board[x].size() <= y || y < 0){return 0;}
    else {
        board[x][y] = std::make_unique<Piece>(disp,betza,tm);
        if (betza == "K"){
            board[x][y]->royal = 1;
            royals[tm] = std::pair(x,y);
        }
    }
    return 1;
}

Game default_daichess(){
    Game g = Game(16, 16);
    std::string start[8][16] {
        // lowest y                                   //highest y
        {"WB","WDD","R","FAA","NB","HFD","WFDNA","Z","Z","WFDNA","HFD","NR","FAA","R","WDD","WB"}, // highest x
        {"R","Z","FC","WF","FN","WC","B","Q","K","B","WC","FN","WF","FC","Z","R"},
        {"FD","B","WA","N","FD","WD","F","N","N","F","WD","FD","N","WA","B","FD"},
        {"P","P","P","P","P","P","P","P","P","P","P","P","P","P","P","P"},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""}                                          // lowest x
        /*
        mirror
        .
        .
        .
        */
    };
    std::string namestart[16][16] {
        // lowest y                                   //highest y
        {"WB ","WDD"," R ","FAA","NB ","HFD"," L "," Z "," Z "," L ","HFD","NR ","FAA"," R ","WDD","WB "}, // highest x
        {" R "," Z ","FC ","WF ","FN ","WC "," B "," Q "," K "," B ","WC ","FN ","WF ","FC "," Z "," R "},
        {"FD "," B ","WA "," N ","FD ","WD "," F "," N "," N "," F ","WD ","FD "," N ","WA "," B ","FD "},
        {" P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        {"","","","","","","","","","","","","","","",""},
        /*
        mirror
        .
        .
        .
        */
    };
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 16; j++){
            int arrayx = (i<8)?i:15-i;
            std::string name = namestart[arrayx][j];
            if (i >=8){
                for (unsigned int k = 0; k<name.length(); k++){
                    if (name[k] != ' '){
                        name[k] += 'a'-'A';
                    }
                }
            }
            g.placepiece(i,j,name,start[arrayx][j],(i<8)?'w':'b'); // code...
        }
    }
    

    return g;
}

std::string algebraic_x(int x){ // rank
    return std::to_string(x+1);
}
std::string algebraic_y(int y){
    std::string s;
    y+=1;
    while (y > 0) {
        --y;
        char d = 'a' + (y%26); 
        y/= 26;
        s = d + s;
    }
    return s;
}

std::string algebraic_pos(int x, int y){ // rank is x coordinate!!
    std::string s;
    y+=1;
    while (y > 0) {
        --y;
        char d = 'a' + (y%26); 
        y/= 26;
        s = d + s;
    }
    return s + std::to_string(x + 1);
}
std::string algebraic_pos(std::pair<int,int> p){ return algebraic_pos(p.first,p.second);}

#include <iostream>
std::pair<int,int> pos_algebraic(std::string s){ // rank is x coord
    int x = -1;
    int y = -1;
    unsigned int bdry = 0;
    for (int i = 0; i<(int)s.length(); i++){
        if (s[i] >= '0' && s[i] <= '9'){
            bdry = i; break;
        }
    }
    x = std::atoi(s.substr(bdry).c_str()) - 1;
    std::string t = s.substr(0,bdry);
    if (bdry > 0){
        y = 0;
    }
    for (int i = 0; i<(int) t.length();i++){
        y*=26;
        y+=t[i]-'a'+1;
    }
    --y;
    

    return std::make_pair(x,y);
}

std::string Game::display_board(bool side){ // to do: unify
    #if DISPLAYLEN < 1
    throw "the pieces on the ground. grumble about the fact that the game cannot render if DISPLAYLEN < 1.";
    #endif
    std::string s;
    std::string e = std::string(DISPLAYLEN,' ');
    e[DISPLAYLEN/2] = '.';
    if (!side) { 
    /*   rank
         +
         ^
         |
    - <--+--> + file
         |
         v
        -
    */
    s+=std::string(DISPLAYLEN+3,' ');
    for (int j = 0; j < (int) width; ++j){
        std::string t = algebraic_y(j);
        t.resize(DISPLAYLEN+1,' ');
        s+=t;
    }
    s+="\n";
    for (int i = (int)height-1; i>=0; --i){
        std::string t = algebraic_x(i);
        t.resize(DISPLAYLEN+1,' ');
        s+=t+" ";
        for (int j = 0; j < (int)width; ++j){
            if (i >= 0 && j >= 0 && i<(int)board.size() && j < (int)board[i].size()){
                if (board[i][j]){
                    s+= board[i][j]->display;
                } else {s+= e;}
            }
            else {s+= std::string(DISPLAYLEN,' ');}
            s+=' ';
        }
        s+= algebraic_x(i);
        s+= '\n';
    }
    s+=std::string(DISPLAYLEN+3,' ');
    for (int j = 0; j < (int) width; ++j){
        std::string t = algebraic_y(j);
        t.resize(DISPLAYLEN+1,' ');
        s+=t;
    }
    } else {
    /*   rank
         -
         ^
         |
    + <--+--> - file
         |
         v
         +
    */
    s+=std::string(DISPLAYLEN+3,' ');
    for (int j = (int) width-1; j>0; --j){
        std::string t = algebraic_y(j);
        t.resize(DISPLAYLEN+1,' ');
        s+=t;
    }
    s+="\n";
    for (int i = 0; i < (int)height; ++i){
        std::string t = algebraic_x(i);
        t.resize(DISPLAYLEN+1,' ');
        s+=t+" ";
        for (int j =(int)width-1; j >=0; --j){
            if (i >= 0 && j>= 0 && i<(int)board.size() && j < (int)board[i].size()){
                if (board[i][j]){
                    s+= board[i][j]->display;
                } else {s+= e;}
            }
            else {s+= std::string(DISPLAYLEN,' ');}
            s+=' ';
        }
        s+= algebraic_x(i);
        s+= '\n';
    }
    s+=std::string(DISPLAYLEN+3,' ');
    for (int j = (int) width-1; j>0; --j){
        std::string t = algebraic_y(j);
        t.resize(DISPLAYLEN+1,' ');
        s+=t;
    }
    }
    return s + "\n";
}



std::unordered_set<std::pair<int,int>,p_hash> Game::accessible_moves(int x, int y, char curr_pl){
    std::unordered_set<std::pair<int,int>,p_hash> mvs;
    if (x < 0 || x >(int) board.size() || y < 0 || y > (int) board[x].size()){ // is the move on the board
    return mvs;
    }
    if (!(board[x][y])){ // are you moving a piece?
        return mvs;
    }
    if (board[x][y]->team != curr_pl){ // do you control that piece?
        return mvs;
    }
    int f_sn = 1;
    int r_sn = 1;
    if (curr_pl == 'w'){ // forward is +x. right is +y.
        f_sn = 1; r_sn = 1;
    } else if (curr_pl == 'b'){ // forward is -x. right is -y.
        f_sn = -1; r_sn = -1;
    }

    Moveset* m_set = &(board[x][y]->moves);

    bool njflag = 0; int aux = 0;
    // to do: inmplement non-jumping properly
    for (auto it = m_set->mleaps.begin(); it!=m_set->mleaps.end(); it++){
        aux = it->second; if (aux < 0){njflag = 1; aux = -aux-1;}
        int x1 = ((it->first.first)*f_sn)+x; // it->first is the move. it->second is the aux value
        int y1 = ((it->first.second)*r_sn)+y;
        if (x1 >= 0 && x1 < (int) board.size() && y1 >= 0 && y1 < (int) board[x1].size()){
            if (!(board[x1][y1])){
                mvs.insert(std::make_pair(x1,y1));
            }
        }
    }
    for (auto it = m_set->cleaps.begin(); it!=m_set->cleaps.end(); it++){
        aux = it->second; if (aux < 0){njflag = 1; aux = -aux-1;}
        int x1 = ((it->first.first)*f_sn)+x;
        int y1 = ((it->first.second)*r_sn)+y;
        if (x1 >= 0 && x1 < (int) board.size() && y1 >= 0 && y1 < (int) board[x1].size()){
            if ((board[x1][y1])&&(board[x1][y1]->team != curr_pl)){
                mvs.insert(std::make_pair(x1,y1));
            }
        }
    }
    for (auto it = m_set->mrides.begin(); it!=m_set->mrides.end(); it++){
        aux = it->second; if (aux < 0){njflag = 1; aux = -aux-1;}
        int x1 = x;
        int y1 = y;
        int dist = 0;
        while (aux == 0 || dist < aux){
            x1 += ((it->first.first)*f_sn);
            y1 += ((it->first.second)*r_sn);
            if (x1 >= 0 && x1 < (int) board.size() && y1 >= 0 && y1 < (int) board[x1].size()){
                if (!(board[x1][y1])){
                    mvs.insert(std::make_pair(x1,y1));
                } else {break;}
            } else {break;}
            ++dist;
        }
    }
    for (auto it = m_set->crides.begin(); it!=m_set->crides.end(); it++){
        aux = it->second; if (aux < 0){njflag = 1; aux = -aux-1;}
        int x1 = x;
        int y1 = y;
        int dist = 0;
        while (aux == 0 || dist < aux){
            x1 += ((it->first.first)*f_sn);
            y1 += ((it->first.second)*r_sn);
            if (x1 >= 0 && x1 < (int) board.size() && y1 >= 0 && y1 < (int) board[x1].size()){
                if ((board[x1][y1])){
                    if (board[x1][y1]->team != curr_pl){
                        mvs.insert(std::make_pair(x1,y1));
                    }
                    break;
                } else {
                    //do not break
                }
            } else {break;}
            ++dist;
        }
    }
    return mvs;
}

bool Game::accesses(int x0, int y0, int x1, int y1){// does not account for check
    int f_sn = 1;
    int r_sn = 1;
    bool capt = 0;
    if (haspiece(x0,y0) && withinbounds(x1,y1)){
        if (board[x0][y0]->team == 'b'){ // really I should implement facing here instead of hardcoding based on team. 
            f_sn = 1; r_sn = 1;
        } else if (board[x0][y0]->team == 'w'){
           f_sn = -1; r_sn = -1;
        }
        if (board[x1][y1]){
            capt = 1;
        } else {
            capt = 0;
        }
        int xdisp = (x1-x0)*f_sn;
        int ydisp = (y1-y0)*r_sn;
        if (capt){
            // leaps
            if (board[x0][y0]->moves.cleaps.contains(std::pair(xdisp,ydisp))){return true;}; // todo nonjumping

            // rides
            for (auto it = board[x0][y0]->moves.crides.begin(); it!=board[x0][y0]->moves.crides.end(); it++){
                bool njflag = 0;
                if (xy_divides_zw(it->first.first,it->first.second,xdisp,ydisp)){
                    int aux = it->second; if (aux < 0){njflag = 1; aux = -aux-1;}
                    int x_1 = x0;
                    int y_1 = y0;
                    int dist = 0;
                    while (aux == 0 || dist < aux){
                        x_1 += ((it->first.first)*f_sn);
                        y_1 += ((it->first.second)*r_sn);
                        if (withinbounds(x_1,y_1)){
                            if (x1 == x_1 && y1 == y_1){
                                return true;
                            } else {
                                if (board[x_1][y_1]){
                                    break;
                                }
                            }
                        } else {break;}
                        ++dist;
                    }
                }
            }
        } else {
            // leaps
            if (board[x0][y0]->moves.mleaps.contains(std::pair(xdisp,ydisp))) {return true;}; // todo nonjumping

            // rides
            for (auto it = board[x0][y0]->moves.mrides.begin(); it!=board[x0][y0]->moves.mrides.end(); it++){
                bool njflag = 0;
                if (xy_divides_zw(it->first.first,it->first.second,xdisp,ydisp)){
                    int aux = it->second; if (aux < 0){njflag = 1; aux = -aux-1;}
                    int x_1 = x0;
                    int y_1 = y0;
                    int dist = 0;
                    while (aux == 0 || dist < aux){
                        x_1 += ((it->first.first)*f_sn);
                        y_1 += ((it->first.second)*r_sn);
                        if (withinbounds(x_1,y_1)){
                            if (x1 == x_1 && y1 == y_1){
                                return true;
                            } else {
                                if (board[x_1][y_1]){
                                    break;
                                }
                            }
                        } else {break;}
                        ++dist;
                    }
                }
            }
        }
    }
    return false;
} 


std::string Game::display_moves(int x, int y){
    if (withinbounds(x,y)){
        Piece* pc = getpc(x,y);
        std::string s;
        if (pc){
            s = ((pc->display + " (") + pc->team) + "): ";
            std::unordered_set<std::pair<int,int>,p_hash> mfdhsadfj = accessible_moves(x,y,pc->team);
            for (auto it = mfdhsadfj.begin(); it != mfdhsadfj.end(); ){
                s+= algebraic_pos(*it);
                it++;
                if (it!= mfdhsadfj.end()){s+= ", ";}
            }
        }
        return s;
    } else {return "";}
}

bool Game::mov(int x0, int y0, int x1, int y1){
    if (withinbounds(x0,y0) && withinbounds(x1,y1) && board[x0][y0]){
        if (board[x0][y0]->royal){
            royals[board[x0][y0]->team] = std::make_pair(x1,y1);
        }
        if (board[x1][y1]){
            board[x1][y1].reset();
        }
        std::swap(board[x0][y0],board[x1][y1]);
        return 1;
    } else {
        return 0;
    }
}