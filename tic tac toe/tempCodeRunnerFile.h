

class TicTacToe{
    int T[3][3];
public :
    TicTacToe();
    void affichage();
    int JeuOrdi(int & bestMove);
    int JeuHumain(int & bestMove);
    int arbitre();
    void CoupHumain();
    void Partie(int resultat_piece