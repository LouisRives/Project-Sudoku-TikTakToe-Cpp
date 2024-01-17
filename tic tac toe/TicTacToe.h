#ifndef _TICTACTOE_H_
#define _TICTACTOE_H_
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class TicTacToe{
    int T[3][3];
public :
    TicTacToe();
    TicTacToe(const TicTacToe & x);
    void affichage();
    int JeuOrdi(int & bestMoveL, int & bestMoveC);
    int JeuHumain(int & bestMoveL, int & bestMoveC);
    int arbitre();
    void CoupHumain();
    void CoupOrdi();
    void Partie(int resultat_piece);
};

#endif
