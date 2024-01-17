#include "TicTacToe.h"

TicTacToe::TicTacToe(){
    for (int i=0; i<3; i++){
       for (int y=0; y<3; y++)
            T[i][y]=0;
    } 
}

TicTacToe::TicTacToe(const TicTacToe & x){
    for (int i=0; i<3; i++){
       for (int y=0; y<3; y++)
            T[i][y]=x.T[i][y];
    } 
}

void TicTacToe::affichage(){
    cout<<"----------------";
    for (int i=0; i<3; i++){
       cout<<endl<<"| "; 
       for (int y=0; y<3; y++){
            if(T[i][y] == -1)
                cout<<T[i][y]<<" | ";
            else 
                cout<<" "<<T[i][y]<<" | ";
       }
    }
    cout<<endl<<"----------------"<<endl;
}

int TicTacToe::arbitre(){
    for (int i=0; i<3;i++){                                        
        if ((T[i][0]== 1 && T[i][1]== 1 && T[i][2]== 1) ||        
            (T[0][i]== 1 && T[1][i]== 1 && T[2][i]== 1) ||         
            (T[0][0]== 1 && T[1][1]== 1 && T[2][2]== 1) ||         
            (T[2][0]== 1 && T[1][1]== 1 && T[0][2]== 1)
            ) return 1; //cl'ordinateur gagne

        else if ((T[i][0]== 2 && T[i][1]== 2 && T[i][2]== 2) ||
                 (T[0][i]== 2 && T[1][i]== 2 && T[2][i]== 2) ||
                 (T[0][0]== 2 && T[1][1]== 2 && T[2][2]== 2) ||
                 (T[2][0]== 2 && T[1][1]== 2 && T[0][2]== 2)
                 ) return -1; // l'humain gagne
    }
    bool verif_egalite=true;
    for (int egaL=0; egaL<3; egaL++){
        for (int egaC=0; egaC<3; egaC++){
            if (T[egaL][egaC]==0){
                verif_egalite=false;
            }
        }    
    }
    if (verif_egalite==true)
        return 0;
    else 
        return -2;
}

void TicTacToe::CoupHumain(){
    int l=10, c=10;
    while (((*this).T[l][c]==1 && (*this).T[l][c]==-1) || l>2 || l<0 || c>2 || c<0){
        cout<<"Veuillez entrer une case (ligne puis colonne): ";
        cin>>l;
        cin>>c;
        if(((*this).T[l][c]==1 && (*this).T[l][c]==-1) || l>2 || l<0 || c>2 || c<0)
            cout<<"Case invalide, veuillez choisir une autre case : "<<endl;
    }
    (*this).T[l][c]=-1;
}

void TicTacToe::CoupOrdi(){
    int c,l;
    TicTacToe Plateau_temp((*this));
    Plateau_temp.JeuOrdi(c,l);
    T[c][l]=1;
}

int piece(){
    srand(time(NULL));
    int a=rand()%2;
    return a;
}

int TicTacToe::JeuHumain(int & bestMoveL, int & bestMoveC){
    int argc, argl, res, val=100;

    if (arbitre()==0)
        return 0;
    if (arbitre()==-1)
        return -100; 

    for (int i=0; i<3; i++){
       for (int y=0; y<3; y++){
            if(T[i][y]==0){
                T[i][y]=-1;
                res= JeuOrdi(argc,argl);
                T[i][y] = 0;
                if(res<val){
                    val=res;
                    bestMoveL=i;
                    bestMoveC=y;
                }
            }
       }
    }
    return(val);
}

int TicTacToe::JeuOrdi(int & bestMoveL, int & bestMoveC){
    int argc, argl, res, val=-100;

    if (arbitre()==0)
        return 0;
    if (arbitre()==1)
        return 100; 
    
    bestMoveL=bestMoveL=0;

    for (int i=0; i<3; i++){
       for (int y=0; y<3; y++){
            if(T[i][y]==0){
                T[i][y]=1;
                res= JeuHumain(argc,argl);
                T[i][y] = 0;

                if(res>val){
                    val=res;
                    bestMoveL=i;
                    bestMoveC=y;
                }
            }
       }
    }
    return(val);
}

void TicTacToe::Partie(int resultat_piece){
    int nouvelle_piece;
    while (arbitre()==-2){
        if (resultat_piece==1){
            CoupHumain();
            affichage();
            nouvelle_piece=0;
        }
        else { 
            CoupOrdi();

            cout<<"Coup Ordinateur : "<<endl;
            affichage();
            nouvelle_piece=1;
        }
        resultat_piece=nouvelle_piece;
    }
    if (arbitre()==-1){
        cout<<endl<<"------------------ VICTOIRE ------------------";
    }
    else if (arbitre()==1){
        cout<<endl<<"------------------ DEFAITE ------------------";
    }
    else {
        cout<<endl<<"------------------ EGALITE ------------------";
    }
}



/*

*/

