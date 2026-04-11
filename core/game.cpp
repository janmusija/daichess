//
// game.cpp
// 2026-034-05
// daichess
//

#include "core/game.h"
#include <string>

#include <iostream>


#define DISPLAYLEN 3

Game::Game(int x, int y){
    board.clear();
    players = {'w','b'};
    curr_pl = 0;
    width = y;
    height = x;
    for (int i = 0; i<x; i++){
        board.emplace_back(y); //yes, this creates a vector of y many nullpointers, *obviously*
    }
}

Game::Game(int x, int y, std::vector<char>&& p){
    board.clear();
    players = p;
    curr_pl = 0;
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

bool Game::placepiece(int x, int y, std::string disp, std::string betza, char tm){
    if (betza == ""){return 0;}
    else if ((int) board.size() <= x || x < 0 || (int) board[x].size() <= y || y < 0){return 0;}
    else {
        board[x][y] = std::make_unique<Piece>(disp,betza,tm);
        board[x][y]->initialize();
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
        {"R","Z","FC","WFiW2iF2","FN","WC","B","Q","K","B","WC","FN","WFiW2iF2","FC","Z","R"},
        {"FDiF2iD2","B","WAiW2iA2","NiN2","FDiF2iD2","WDiW2iD2","FiF2","NiN2","NiN2","FiF2","WDiW2iD2","FDiF2iD2","NiN2","WAiW2iA2","B","FDiF2iD2"},
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
    {
        {   // rook
            std::pair<std::string,std::string> jon = std::make_pair(" R ","R");
            g.promo["R"] = std::make_pair(jon,1);
            g.promo["rook"] = std::make_pair(jon,0);
        }
        {   // double store
            std::pair<std::string,std::string> jon = std::make_pair(" B ","B");
            g.promo["B"] = std::make_pair(jon,1);
            g.promo["bishop"] = std::make_pair(jon,0);
        }
        {   // knight
            std::pair<std::string,std::string> jon = std::make_pair(" N ","N");
            g.promo["N"] = std::make_pair(jon,1);
            g.promo["knight"] =  std::make_pair(jon,0);
        }
        {   // queen
            std::pair<std::string,std::string> jon = std::make_pair(" Q ","Q");
            g.promo["Q"] = std::make_pair(jon,1);
            g.promo["RB"] = std::make_pair(jon,0);
            g.promo["queen"] = std::make_pair(jon,0);
        }
        {   // WB / dragon horse
            std::pair<std::string,std::string> jon = std::make_pair("WB ","WB");
            g.promo["WB"] = std::make_pair(jon,1);
            g.promo["motherfucking dragon horse"] = std::make_pair(jon,0);
            g.promo["dragon horse"] = std::make_pair(jon,0);
        }
        {   // wader
            std::pair<std::string,std::string> jon = std::make_pair("WDD","WDD");
            g.promo["WDD"] = std::make_pair(jon,1);
            g.promo["wader"] = std::make_pair(jon,0);
        }
        {   // faalcon
            std::pair<std::string,std::string> jon = std::make_pair("FAA","FAA");
            g.promo["FAA"] = std::make_pair(jon,1);
            g.promo["faalcon"] = std::make_pair(jon,0);
        }
        {   // archbishop
            std::pair<std::string,std::string> jon = std::make_pair("NB ","NB");
            g.promo["NB"] = std::make_pair(jon,1);
            g.promo["archbishop"] = std::make_pair(jon,0);
            g.promo["enby"] = std::make_pair(jon,0);
            g.promo["princess"] = std::make_pair(jon,0);
            g.promo["cardinal"] = std::make_pair(jon,0);
        }
        {   // halfduck
            std::pair<std::string,std::string> jon = std::make_pair("HFD ","HFD");
            g.promo["HFD"] = std::make_pair(jon,1);
            g.promo["halfduck"] = std::make_pair(jon,0);
        }
        /*
        {   // WAH
            std::pair<std::string,std::string> jon = std::make_pair("WAH","WAH");
            g.promo["WAH"] = jon;
            g.promo["waluigi"] = jon;
        }
        */
        /*
        {   // ZNG
            std::pair<std::string,std::string> jon = std::make_pair("ZNG","ZNG");
            g.promo["ZNG"] = jon;
            g.promo["zing"] = jon;
            g.promo["zing!!"] = jon;
        }
        */
        /*  // not sure if I want to keep lions, especially as sth you can promote to
        {   // lion
            std::pair<std::string,std::string> jon = std::make_pair(" L ","WFDNA");
            g.promo["WFDNA"] = jon;
            g.promo["L"] = jon;
            g.promo["lion"] = jon;
        }
        */
        {   // zebra
            std::pair<std::string,std::string> jon = std::make_pair(" Z ","Z");
            g.promo["Z"] = std::make_pair(jon,1);
            g.promo["J"] = std::make_pair(jon,0);
            g.promo["zebra"] = std::make_pair(jon,0);
        }
        {   // wizard
            std::pair<std::string,std::string> jon = std::make_pair("FC ","FC");
            g.promo["FC"] = std::make_pair(jon,1);
            g.promo["FL"] = std::make_pair(jon,0);
            g.promo["wizard"] = std::make_pair(jon,0);
        }
        {   // woody rook
            std::pair<std::string,std::string> jon = std::make_pair("WD ","WD");
            g.promo["WD"] = std::make_pair(jon,1);
            g.promo["woody rook"] = std::make_pair(jon,0);
        }
        {   // man / commoner
            std::pair<std::string,std::string> jon = std::make_pair("WF ","WF");
            g.promo["WF"] = std::make_pair(jon,1);
            g.promo["man"] = std::make_pair(jon,0);
            g.promo["commoner"] = std::make_pair(jon,0);
        }
        {   // kirin
            std::pair<std::string,std::string> jon = std::make_pair("FD ","FD");
            g.promo["FD"] = std::make_pair(jon,1);
            g.promo["kirin"] = std::make_pair(jon,0);
        }
        {   // WC / lightweight 
            std::pair<std::string,std::string> jon = std::make_pair("WC ","WC");
            g.promo["WC"] = std::make_pair(jon,1);
            g.promo["LW"] = std::make_pair(jon,0);
            g.promo["watercloset"] = std::make_pair(jon,0);
            g.promo["toilet"] = std::make_pair(jon,0);
            g.promo["lightweight"] = std::make_pair(jon,0);
        }
        {   // NR // chancellor // empress
            std::pair<std::string,std::string> jon = std::make_pair("NR ","NR");
            g.promo["NR"] = std::make_pair(jon,1);
            g.promo["chancellor"] = std::make_pair(jon,0);
            g.promo["empress"] = std::make_pair(jon,0);
            g.promo["marshal"] = std::make_pair(jon,0);
        }
        {   // WA // phoenix // waffle
            std::pair<std::string,std::string> jon = std::make_pair("WA ","WA");
            g.promo["WA"] = std::make_pair(jon,1);
            g.promo["waffle"] = std::make_pair(jon,0);
            g.promo["phoenix"] = std::make_pair(jon,0);
        }
        {   // F // ferz
            std::pair<std::string,std::string> jon = std::make_pair(" F ","F");
            g.promo["F"] = std::make_pair(jon,1);
            g.promo["ferz"] = std::make_pair(jon,0);
            g.promo["pay respects"] = std::make_pair(jon,0);
            g.promo["i dont need no chunky pieces"] = std::make_pair(jon,0);
        }
        /* piece code
        {"WB","WDD","R","FAA","NB","HFD","WFDNA","Z","Z","WFDNA","HFD","NR","FAA","R","WDD","WB"},
        {"R","Z","FC","WFiW2iF2","FN","WC","B","Q","K","B","WC","FN","WFiW2iF2","FC","Z","R"},
        {"FDiF2iD2","B","WAiW2iA2","NiN2","FDiF2iD2","WDiW2iD2","FiF2","NiN2","NiN2","FiF2","WDiW2iD2","FDiF2iD2","NiN2","WAiW2iA2","B","FDiF2iD2"},
        {"P","P","P","P","P","P","P","P","P","P","P","P","P","P","P","P"},
        
        names
        {"WB ","WDD"," R ","FAA","NB ","HFD"," L "," Z "," Z "," L ","HFD","NR ","FAA"," R ","WDD","WB "},
        {" R "," Z ","FC ","WF ","FN ","WC "," B "," Q "," K "," B ","WC ","FN ","WF ","FC "," Z "," R "},
        {"FD "," B ","WA "," N ","FD ","WD "," F "," N "," N "," F ","WD ","FD "," N ","WA "," B ","FD "},
        {" P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "," P "},
        */
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
    bool uncastledking = 0;
    if (board[x][y]->royal && board[x][y]->flag.contains("uncastled")){
        uncastledking = 1;
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
    if (uncastledking){
        for (int dir = 0; dir < 4; dir++){
            int x1 = x; int y1 = y;
            switch (dir) {
                case 0: x1 = x+2; break;
                case 1: x1 = x-2; break;
                case 2: y1 = y+2; break;
                case 3: y1 = y-2; break;
            }
            if (validcastle(x,y,x1,y1)){
                mvs.insert(std::make_pair(x1,y1));
            }
        }
    }

    return mvs;
}

bool Game::accesses_castle(int x0, int y0, int x1, int y1, int& tx, int& ty){// does not account for check
    tx = -1; ty = -1;
    int f_sn = 1;
    int r_sn = 1;
    bool capt = 0;
    if (haspiece(x0,y0) && withinbounds(x1,y1)){
        if (board[x0][y0]->team == 'b'){ // really I should implement facing here instead of hardcoding based on team. 
            f_sn = -1; r_sn = -1;
        } else if (board[x0][y0]->team == 'w'){
           f_sn = 1; r_sn = 1;
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
            // castling
            if (validcastle(x0,y0,x1,y1,tx,ty)){
                return true;
            }
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
            std::unordered_set<std::pair<int,int>,p_hash> mfdhsadfj = legal_moves(x,y,pc->team);
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
        if (board[x0][y0]->flag.contains("i")){ // unmoved pieces
            board[x0][y0]->prune_init_moves();
        }
        std::swap(board[x0][y0],board[x1][y1]);
        return 1;
    } else {
        return 0;
    }
}

bool Game::incheck(char pl){
    if (!royals.contains(pl)){
        return false;
    }
    int rx = royals[pl].first;
    int ry = royals[pl].second;

    for (int i = 0; i< (int) board.size(); i++){
        for (int j = 0; j < (int) board[i].size(); j++){
            if (board[i][j] && board[i][j]->team!= pl){
                if (accesses(i,j,rx,ry)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool Game::suspend_move(int x0, int y0, int x1, int y1){ // suspend current pieces at (x0,y0) and (x1,y1). place dummy piece of same team as (x0,y0) at (x1,y1)
    if (haspiece(x0,y0) && withinbounds(x1,y1)){
        susp_src = std::make_unique<Piece>(board[x0][y0]->team, board[x0][y0]->royal);
        susp_dest.reset();
        if (board[x0][y0]->royal){
            royals[board[x0][y0]->team] = std::make_pair(x1,y1);
        }
        std::swap(board[x0][y0],susp_src);
        std::swap(board[x1][y1],susp_dest);
        std::swap(board[x0][y0],board[x1][y1]);
        return 1;
    }
    return 0;
}

void Game::reset_suspension(int x0, int y0, int x1, int y1){ //undo that and destroy dummy piece
    if (susp_src->royal){
        royals[susp_src->team] = std::make_pair(x0,y0);
    }
    std::swap(board[x0][y0],susp_src);
    std::swap(board[x1][y1],susp_dest);
    susp_src.reset();
    susp_dest.reset();
}

bool Game::legal(int x0, int y0, int x1, int y1, char pl){
    int tx = -1; int ty = -1;
    if (!accesses_castle(x0,y0,x1,y1,tx,ty)){
        return false;
    }
    if (board[x0][y0]->team != pl){
        return false;
    }
    if (move_into_check_legal){
        return true;
    }
    if (tx != -1){
        Game g = copy();
        int vx = x1 - x0; int vy = y1 - y0; vx = vx/2; vy = vy/2;
        g.mov(x0,y0,x1,y1);
        g.mov(tx,ty,x0+vx,y0+vy);
        if (g.incheck(pl)){
            return false;
        }
        return true;
    } else {
        bool a = suspend_move(x0,y0,x1,y1);
        bool b = true;
        if (incheck(pl)){
            b = false;
        }
        if (a) {reset_suspension(x0,y0,x1,y1);}
        return b;
    }
    // TK --  make sure this works
}

bool Game::validcastle(int x0, int y0, int x1, int y1, int& tx, int& ty, int& rooklen){
    if (haspiece(x0,y0) && board[x0][y0]->royal && board[x0][y0]->flag.contains("uncastled")){
        int vx = x1-x0; int vy = y1 - y0;
        if (vx*vx + vy*vy == 4){ // this is a terrible hack to ensure that the move is a (2,0) move
            int _x_ = x0; int _y_ = y0; int step = 0;
            vx /= 2; vy /=2;
            do {
                _x_ += vx; _y_ += vy; ++step;
                if (haspiece(_x_,_y_) && board[_x_][_y_]->flag.contains("uncastled") && (board[_x_][_y_]->betza == "R") && board[_x_][_y_]->team == board[x0][y0]->team && step > 2){
                    tx = _x_; ty = _y_; rooklen = std::abs(x0+vx-_x_+y0+vy-_y_); return true;
                } 
            } while (withinbounds(_x_,_y_) && !board[_x_][_y_]);
        }         
    }
    return false;  
}

bool Game::hasmoves(char pl){
    for (int i = 0; i< (int) board.size(); i++){
        for (int j = 0; j < (int) board[i].size(); j++){
            if (board[i][j] && board[i][j]->team== pl){
                if (!legal_moves(i,j,pl).empty()){
                    return 1;
                }
            }
        }
    }
    return 0;
}

std::unordered_set<std::pair<int,int>,p_hash> Game::legal_moves(int x, int y, char pl){
    std::unordered_set<std::pair<int,int>,p_hash> am = accessible_moves(x,y,pl);
    std::unordered_set<std::pair<int,int>,p_hash> lm;
    for (auto it = am.begin(); it != am.end(); it++){
        if (legal(x,y,it->first,it->second,pl)){
            lm.insert(*it);
        }
    }
    return lm; 
}

std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash> Game::all_legal_moves(char pl){
    std::unordered_set<std::pair<std::pair<int,int>,std::pair<int,int>>,q_hash> lm;
    for (int x = 0; x < board.size(); x++){
        for (int y = 0; y < board[x].size(); y++){
            if (board[x][y] && board[x][y]->team == pl){
                std::unordered_set<std::pair<int,int>,p_hash> am = accessible_moves(x,y,pl);
                for (auto it = am.begin(); it != am.end(); it++){
                    if (legal(x,y,it->first,it->second,pl)){
                        lm.insert(std::make_pair(std::make_pair(x,y),*it));
                    }
                }
            }
        }
    }
    return lm; 
}

void Game::append_to_alg(int x0, int y0, int x1, int y1){// call before mov();
    append_to_alg(algebraic_pos(x0,y0),algebraic_pos(x1,y1));
} 
void Game::append_to_alg(std::string s0, std::string s1){
    algebraic_history += (s0 + " -> " + s1 + ", ");
}

Game::Game(const Game & g){
    width = g.width;
    height = g.height;
    turnctr = g.turnctr;
    algebraic_history = g.algebraic_history;
    royals = g.royals;
    players = g.players;
    curr_pl = g.curr_pl;
    move_into_check_legal = g.move_into_check_legal;

    for (int i = 0; i<(int)height; i++){
        board.emplace_back(width);
        for (int j = 0; j<(int) width; j++){
            if (g.board[i][j])
            board[i][j] = std::make_unique<Piece>(*(g.board[i][j]));
        }
    }
}

Game Game::copy(){
    Game h(*this);
    return h;
}