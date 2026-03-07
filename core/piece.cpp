//
// piece.cpp
// 2026-034-05
// daichess
//

#include "core/piece.h"

void Moveset::addmove(std::pair<int,int> m,bool isride, int mc, int aux){
    if (isride){
        if (mc <= 0) { // captures
            crides.insert({m,aux});
        }
        if (mc >= 0){ //moves
            mrides.insert({m,aux});
        }
    } else {
        if (mc <= 0) { // captures
            cleaps.insert({m,aux});
        }
        if (mc >= 0){ //moves
            mleaps.insert({m,aux});
        }
    }
}

Moveset::Moveset(){}

Moveset::Moveset(std::string bnot){
    char firstdir = ' ';
    char secondir = ' ';
    bool captures = 1;
    bool moves = 1;
    bool njflag = 0;
    int i = 0;
    while (i < (int) bnot.length()){
        if (bnot[i] == 'm' ) {
            captures = 0;
            moves = 1;
        } else if (bnot[i] == 'c'){
            captures = 1;
            moves = 0;
        } else if (bnot[i] == 'n'){
            njflag = 1; // nonjump unimplemented
        }

        // atomic pieces. Only supported atoms are W F D N A H C Z G and R B
        else if (bnot[i] == 'W' || bnot[i] == 'F' || bnot[i] == 'D' || bnot[i] == 'N' || bnot[i] == 'A' || bnot[i] == 'H' || bnot[i] == 'C' || bnot[i] == 'Z' || bnot[i] == 'G' || bnot[i] == 'R' || bnot[i] == 'B'){
            int nexti = i+1;
            bool ride = 0;
            int aux = 0;
            if ((int) bnot.length() > i+1 && bnot[i+1] == bnot[i]){
                ride = 1;
                nexti++;
            }
            std::pair<int,int> mov;
            switch (bnot[i]){
                case 'R' :
                    ride = 1;
                    mov = std::make_pair(1,0);
                break;
                case 'W' : 
                    mov = std::make_pair(1,0);
                break;
                case 'B' :
                    ride = 1;
                    mov = std::make_pair(1,1);
                break;
                case 'F' : 
                    mov = std::make_pair(1,1);
                break;
                case 'D' : 
                    mov = std::make_pair(2,0);
                break;
                case 'N' : 
                    mov = std::make_pair(2,1);
                break;
                case 'A' : 
                    mov = std::make_pair(2,2);
                break;
                case 'H' : 
                    mov = std::make_pair(3,0);
                break;
                case 'C' : 
                    mov = std::make_pair(3,1);
                break;
                case 'Z' : 
                    mov = std::make_pair(3,2);
                break;
                case 'G' : 
                    mov = std::make_pair(3,3);
                break;
            }

            // later: add support for limited ride length (= aux)

            if (njflag){
                aux = -aux-1;
            }
            std::pair<int,int> move2 = mov;
            bool usem2 = 0;
            if (mov.first != mov.second){
                move2.first = mov.second;
                move2.second = mov.first;
                usem2 = 1;
            }
            /*
             x
          fl ^ fr
             |
         -y<-+->y     ... sorry
             |
          bl v br
            -x
            */
            {
                if (firstdir == ' ' || (firstdir == 'f' && (secondir == 'r' || secondir == ' '))){
                    addmove(mov, ride, moves - captures, aux);
                    if (usem2){
                        addmove(move2, ride, moves-captures, aux);
                    }
                }
                mov.second = -mov.second;
                move2.second = -move2.second;
                if (firstdir == ' ' || (firstdir == 'f' && (secondir == 'l' || secondir == ' '))){
                    addmove(mov, ride, moves - captures, aux);
                    if (usem2){
                        addmove(move2, ride, moves-captures, aux);
                    }
                }
                mov.first = -mov.first;
                move2.first = -move2.first;
                if (firstdir == ' ' || (firstdir == 'b' && (secondir == 'l' || secondir == ' '))){
                    addmove(mov, ride, moves - captures, aux);
                    if (usem2){
                        addmove(move2, ride, moves-captures, aux);
                    }
                }
                mov.second = -mov.second;
                move2.second = -move2.second;
                if (firstdir == ' ' || (firstdir == 'b' && (secondir == 'r' || secondir == ' '))){
                    addmove(mov, ride, moves - captures, aux);
                    if (usem2){
                        addmove(move2, ride, moves-captures, aux);
                    }
                }
            }


            // reset
            captures = 1; moves = 1; firstdir = ' '; secondir = ' ';
            i = nexti;
            break;
        }
        
        
        else if (secondir == ' ' && (bnot[i] == 'f' || bnot[i] == 'b' || bnot[i] == 'l' || bnot[i] == 'r' || bnot[i] == 'h' || bnot[i] == 's' || bnot[i] == 'v')){
            if (firstdir == ' '){
                firstdir = bnot[i];
            } else {
                secondir = bnot[i];
            }
        }

        i++; // default iterator behavior
    }
} 

Piece::Piece(std::string disp, std::string bnot, char tm){
    display = disp;
    betza = bnot;
    team = tm;
    royal = 0;
    if (bnot == "Q"){
        bnot = "RB";
    }
    if (bnot == "K"){ // king. not automatically royal.
        bnot = "WF";
    } else if (bnot == "P"){ // pawn
        bnot = "fmWfcF";
        flag.insert("p"); // pawns are janky and subject to many additional rules
    }
    moves = Moveset(bnot);
}

Piece::Piece(char tm, bool r){
    team = tm;
    royal = r;
}

void Piece::initialize(){
    flag.insert("i");
    if (betza == "K" || betza == "R"){
        flag.insert("uncastled");
    }
}