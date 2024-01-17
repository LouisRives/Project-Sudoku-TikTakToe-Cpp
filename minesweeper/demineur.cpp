#include <iostream>
#include<cstdlib>
#include <stdlib.h>
#include <ctime>

using namespace std;

struct matrice
{
    int nbl ;
    int nbc ;
    int * *T ;
} ;

//Prototype :

void Jeu (int n, int m, matrice *J, matrice *M, int x, int y, int gameover, int victoire, int compteurnonmine, int bonus, clock_t temps);
void creuser(int n, int m, int x, int y, matrice *J,  matrice *M, int gameover, int &victoire, int compteurnonmine, int test, int bonus, clock_t temps);
void creuser_recu (int n, int m, int x, int y, matrice *J,  matrice *M, int gameover, int &victoire, int compteurnonmine, int bonus,clock_t temps);

int * *creer_tab2D(int n, int m)
{
    int * *p=new int *[n] ;
    for(int i=0;i<n;i++) p[i]=new int[m] ;
    return (p);
}

matrice *Creer_matrice(int n , int m)
{
    matrice *p=new matrice ;
    (*p).nbl=n ;
    (*p).nbc=m ;
    (*p).T=creer_tab2D(n,m) ;
    return (p) ;
}

void initZero_mat(matrice & J)
{
    for(int i=0;i<J.nbl;i++)
        for(int j=0;j<J.nbc;j++) J.T[i][j]=0 ;
}

int mine_ou_pas_mine(int probamine, int n, int m, int &compteurnonmine)
{
    int mine=rand()%(m*n+1);
    if (mine<=probamine) mine=2;
    else {
        mine=0;
        compteurnonmine=compteurnonmine+1;
    }
    return mine;
}

matrice Int_jeu(int n, int m, matrice *J, int &compteurnonmine)
{
    int difficulte, probamine;
    while(difficulte<1 || difficulte>3){
        cout<<"Entrez la difficult"<<char (0x82)<<" de la partie (1, 2 ou 3) : ";
        cin>>difficulte;
        if (difficulte<1 || difficulte>3)cout<<"ERREUR : valeur incorrect, veuillez r"<<char (0x82)<<"essayer."<<endl;
    }
    if (difficulte==1)
    {
        probamine=((10*(m*n))/100); //Il y 10% de mines dans le mode de jeu 1 (facile)
    }
    if (difficulte==2)
    {
        probamine=((30*(m*n))/100);//Il y 30% de mines dans le mode de jeu 2 (moyen)
    }
    if (difficulte==3)
    {
        probamine=((45*(m*n))/100);//Il y 45% de mines dans le mode de jeu 3 (difficile)
    }
    for (int z=0; z<n; z++){
        for (int w=0; w<m; w++){
            J->T[z][w]=mine_ou_pas_mine(probamine,n,m, compteurnonmine);
        }
    }
    int solus;
    cout<<"Voulez vous la solution ? (1 = oui, 0 = non) ";
    cin>>solus;
    if (solus==1){
        cout<<"Solution : "<<endl;
        for (int z=0; z<n; z++){
            for (int w=0; w<m; w++){
                    cout<<J->T[z][w]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}

void mines_autour(int n, int m, matrice *J, matrice *M)
{
    for (int z=0; z<n; z++){
        for (int w=0; w<m; w++){
                if (J->T[z][w+1]==2) //Vérifie ss'il y a un drapeau dans la case de la Matrice J à la ligne z et colonne w
                    M->T[z][w]=M->T[z][w]+1;
                if (J->T[z][w-1]==2)
                    M->T[z][w]=M->T[z][w]+1;

            if (z+1<=n){ //Permet d'éviter des problèmes de mémoires en affichant des cases inexistates de la Matrice (ex : s'il y a 4 lignes dans la Matrice et que z+1 = 5, on ne vérifie pas)
                if (J->T[z+1][w]==2)
                    M->T[z][w]=M->T[z][w]+1;
                if (J->T[z+1][w+1]==2)
                    M->T[z][w]=M->T[z][w]+1;
                if (J->T[z+1][w-1]==2)
                    M->T[z][w]=M->T[z][w]+1;
            }

            if (z-1>=0){
                if (J->T[z-1][w]==2)
                    M->T[z][w]=M->T[z][w]+1;
                if (J->T[z-1][w+1]==2)
                    M->T[z][w]=M->T[z][w]+1;
                if (J->T[z-1][w-1]==2)
                    M->T[z][w]=M->T[z][w]+1;
            }
        }
    }
}

void affichage(int n, int m, matrice *J, matrice *M)
{
    cout<<"   ";
    for (int y=0; y<m; y++){
        cout<<y<<" ";
    }
    cout<<endl<<"  ";
    for (int y=0; y<m; y++){
        cout<<"--";
    }
    cout<<endl;
    int x=0;
    for (int z=0; z<n; z++){
        cout<<x<<"| ";
        x=x+1;
        for (int w=0; w<m; w++){
            if (J->T[z][w]==0 || J->T[z][w]==2) //Si la case n'est pas encore creusé
                cout<<char (178); //affiche une case pleine
            if (J->T[z][w]==1) //S’il n’y pas  de mine et la case a été creusée
                cout<<M->T[z][w]; //Affiche le nombre de mines autour de la case
            if (J->T[z][w]==3 || J->T[z][w]==4) //S’il y'a un drapeau
                cout<<char (20);//affiche le symbole paragraphe (ressemblant à un drapeau)
            if (J->T[z][w]==5)
                cout<<"#";
            cout<<" ";
        }
        cout<<endl;
    }
}

void poser_drapeau(int n, int m, int x, int y, matrice *J, matrice *M, int victoire, int compteurnonmine, int bonus, clock_t temps)
{
    if (J->T[x][y]==0) J->T[x][y]=3; //Drapeau s'il n'y avait pas de mine
    else if (J->T[x][y]==2) J->T[x][y]=4; //Drapeau s'il y a une mine
    else cout<<"ERREUR : la case occupe deja un drapeau ! "<<endl;
    Jeu(n, m, J, M, 0, 0, 0, victoire, compteurnonmine,bonus,temps);
}

void lever_drapeau(int n, int m, int x, int y, matrice *J, matrice *M, int victoire, int compteurnonmine, int bonus, clock_t temps)
{
    if (J->T[x][y]==3) J->T[x][y]=0; //Drapeau sans mine -> on enlève le drapeau et on met une case vide
    else if (J->T[x][y]==4) J->T[x][y]=2; //Drapeau avec mine -> on enlève le drapeau et on met une mine
    else cout<<"ERREUR : Cette case n'a pas de drapeau !"<<endl;
    Jeu(n, m, J, M, 0, 0, 0, victoire, compteurnonmine,bonus,temps);
}

void creuser_recursif (int n, int m, int x, int y, matrice *J,  matrice *M, int gameover, int &victoire, int compteurnonmine, int test, int bonus, clock_t temps)
{
    if ((M->T[x][y])>0) {
            return;
    }
    else
    {
        test=1;
        if (x==0)
        {
            if (y==0)
            {
                creuser(n, m, x, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
            }
            else if (y==(M->nbc-1))
            {
                creuser(n, m, x+1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
            }
            else
            {
                creuser(n, m, x, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
            }
        }
        else if (x==(M->nbl-1))
        {
            if (y==0)
            {
                creuser(n, m, x-1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
            }
            else if (y==(M->nbc-1))
            {
                creuser(n, m, x, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
            }
            else
            {
                creuser(n, m, x, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
            }
        }
        else
        {
            if (y==0)
            {
                creuser(n, m, x-1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
            }
            else if (y==(M->nbc-1))
            {
                creuser(n, m, x, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
            }
            else
            {
                creuser(n, m, x, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x-1, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y+1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
                creuser(n, m, x+1, y-1, J,  M, victoire, gameover, compteurnonmine,test,bonus,temps);
            }
        }
    }
}

void creuser(int n, int m, int x, int y, matrice *J,  matrice *M, int gameover, int &victoire, int compteurnonmine, int test, int bonus, clock_t temps)
{
    if (test==1){
        if (J->T[x][y]==0)
        {
            J->T[x][y]=1; // Il n'y a pas de mines donc on affiche le nombres de mines autour de la case.
            victoire=victoire+1;
            creuser_recursif(n, m, x, y, J,  M, victoire, gameover, compteurnonmine, test, bonus,temps);
        }
    }
    else
    {
        if (J->T[x][y]==0)
        {
            J->T[x][y]=1; // Il n'y a pas de mines donc on affiche le nombres de mines autour de la case.
            victoire=victoire+1;
            creuser_recursif(n, m, x, y, J,  M, victoire, gameover, compteurnonmine, test, bonus,temps);
        }
        else if (J->T[x][y]==1)
            cout<<"ERREUR : Vous avez deja creuse cette case."<<endl;
        else if (J->T[x][y]==2) //On creuse une bombe donc le statue gameover passe à 1 pour finir la partie
            gameover=1;
        else if (J->T[x][y]==3 || J->T[x][y]==4)
            cout<<"ERREUR : Il y a un drapeau sur la case, vous ne pouvez donc pas creuser cette case."<<endl;
        Jeu(n, m, J, M, 0, 0, gameover, victoire, compteurnonmine, bonus,temps);
    }
}

void joker (int n, int m, int x, int y, matrice *J,  matrice *M, int gameover, int &victoire, int compteurnonmine, int &bonus, clock_t temps)
{
    if (bonus==0)
        cout<<"Vous avez deja utilise votre joker !";
    else {
        if (J->T[x][y]==1)
            cout<<"ERREUR : Vous avez deja creuse cette case."<<endl;
        if (J->T[x][y]==0)
        {
            bonus=0;
            J->T[x][y]=1;
            victoire=victoire+1;
        }
        if (J->T[x][y]==2)
        {
            bonus=0;
            J->T[x][y]=5;
        }
        if (J->T[x][y]==3 || J->T[x][y]==4)
            cout<<"ERREUR : Il y a un drapeau sur la case, vous ne pouvez donc pas creuser cette case."<<endl;
    }
    Jeu(n, m, J, M, 0, 0, gameover, victoire, compteurnonmine, bonus,temps);
}


void Jeu (int n, int m, matrice *J, matrice *M, int x, int y, int gameover, int victoire, int compteurnonmine, int bonus, clock_t temps)
{
    cout<<"Victoire = "<<victoire<<endl;
    if (victoire==compteurnonmine){
        affichage(n, m, J, M);
        cout<<"!!!--------------------- VICTOIRE ---------------------!!!"<<endl;
        cout<<"Vous avez gagne la partie en : "<<temps/60<<"min et "<<temps%60<<"secs !"<<endl;
        cout<<"!!!----------------------------------------------------!!!"<<endl;
        return;
    }
    if (gameover==0){
        int action=0;
        affichage(n, m, J, M);
        int verif=0;
        temps = clock()/CLOCKS_PER_SEC;
        while (verif!=2){
            cout<<endl<<"------------------------------------------------------------------------"<<endl<<endl;
            cout<<"Choissiez une case (ligne colonne): ";
            cin>>x>>y;
            for(int i=0;i<n;i++)
                if (i==x) verif=verif+1;
            for(int i2=0;i2<m;i2++)
                if (i2==y) verif=verif+1;
            if (verif!=2){
                verif=0;
                cout<<"Cette case n'existe pas veuillez reessayer."<<endl;
            }
        }
        cout<<"Maintenant choissiez une action : "<<endl<<"1 = creuser la case ; 2 = poser un drapeau ; 3 = lever un drapeau ; 4 = utiliser votre Joker (il vous reste "<<bonus<<" joker) : ";
        cin>>action;
        if (action == 1)
            creuser(n,m,x,y,J,M, gameover, victoire,compteurnonmine, 0, bonus,temps);
        if (action == 2)
            poser_drapeau(n,m,x,y,J,M, victoire, compteurnonmine,bonus,temps);
        if (action == 3)
            lever_drapeau(n,m,x,y,J,M, victoire,compteurnonmine,bonus,temps);
        if (action == 4)
            joker(n,m,x,y,J,M, gameover, victoire,compteurnonmine,bonus,temps);
    }
    else cout<<"!!!---------------------GAME OVER---------------------!!!";
}

int main()
{
    clock_t temps;
    srand(time(NULL));
    matrice *J=Creer_matrice(100, 100) ;
    initZero_mat((*J)) ;
    int n=0,m=0, compteurnonmine=0, victoire=0;
    cout<<"Drapeau = "<<char (20)<<endl<<"Bombe apres joker = #"<<endl<<"Case pas encore creusee = "<<char (178)<<endl;
    cout<<"Entrez le nombre de ligne et de colonnes du tableau de jeu (l L) : ";
    cin>>n>>m;
    matrice *M=Creer_matrice(n, m) ;
    initZero_mat((*M)) ;
    Int_jeu(n,m,J,compteurnonmine);
    mines_autour(n, m, J, M);
    Jeu(n, m, J, M, 0, 0, 0, 0, compteurnonmine, 1, temps);
}




