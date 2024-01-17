#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "sudoku.h"


/****************************************/
/* Objectif : Construction d'une cellule
/****************************************/
cellule::cellule(int i, int j)
{
	l=i;
	c=j;
	b=(3*(i/3)+(j/3));
	n=0;
    // A FAIRE !!! (si vous choissisez d'utiliser la classe) //
}


/****************************************/
/* Objectif : Construteur avec argument 
permettant la création d'une grille à partir d'un 
fichier.
/****************************************/
sudoku::sudoku(char filename[])
{
	N=0;
	ifstream file(filename);
	int k;

	for(int i = 0; i < 9; i++)
	{
        for(int j = 1; j <= 9; j++){
			ligne[i][j-1]=false;
			colonne[i][j-1]=false;
			bloc[3*(i/3)+(j/3)][j-1]=false;
		}
	}
    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++){
            file>>grille[i][j];
			k=grille[i][j];
			if (k==0){
				cellule S(i,j) ;
				T[N]=S;
				N++;
			}
			else {
				ligne[i][k-1]=true;
				colonne[j][k-1]=true;
				bloc[3*(i/3)+j/3][k-1]=true;
			}

		}
    }
	for(int k=0;k<N;k++){
		for (int r=1;r<=9;r++){
			if (!ligne[T[k].l][r-1] && !colonne[T[k].c][r-1] && !bloc[T[k].b][r-1]){
				(T[k].n)++ ;
				//cout <<"pour la case [ "<<(T[k].l+1)<<" : "<<(T[k].c)+1<<" : "<<(T[k].b)+1<<" ] "<<"une valeur possible est "<<r<<endl; 
			}
		}
	}
	
}

void sudoku::testligne(){
	cout<<"ligne :"<<endl;
	for (int i=0;i<9;i++){
		for (int k=1;k<=9;k++){
			if (ligne[i][k-1]==true) cout <<k <<" ";
		}
		cout<<endl;
	}
}

void sudoku::testcolonne(){
	cout<<"colonne :"<<endl;
	for (int i=0;i<9;i++){
		for (int k=1;k<=9;k++){
			if (colonne[i][k-1]==true) cout <<k <<" ";
		}
		cout<<endl;
	}
}

void sudoku::testbloc(){
	cout<<"bloc :"<<endl;
	for (int i=0;i<9;i++){
		for (int k=1;k<=9;k++){
			if (bloc[i][k-1]==true) cout <<k <<" ";
		}
		cout<<endl;
	}
}






/****************************************/
/* Objectif : Affichage de la grille sudoku
/****************************************/
void sudoku::affichage()
{
	cout << setw(3) << "-" << "------------------------------------" << endl;
	for(int i = 0; i < 9; i++){
		if((i == 3) || (i == 6))
			cout << setw(3) << "-" << "------------------------------------" << endl;
		cout << setw(3) << "|";		
		for(int j = 0; j < 8; j++){
			if((j == 3) || (j == 6))
				cout << setw(3) << "|" << setw(3) << grille[i][j];
			else
				cout << setw(3) << grille[i][j];
		}
		cout << setw(3) << grille[i][8] << setw(3)<<  "|" << endl;
	}
	cout << setw(3) << "-" << "------------------------------------" << endl;
}


/****************************************/
/* Objectif : Détermination d'une solution de la grilleées.
La méthode renvoie vrai si une solution a été trouvée, 0 sinon
/****************************************/
bool sudoku::solution()
{
	if (backTracking(grille,0,0)) return true;
	return false ;
}

void sudoku::trier(){
	for (int F=N-1;F>0;F--){
		for (int i=0;i<F;i++){
			if (T[i].n>T[i+1].n) {
				cellule tmp=T[i];
				T[i]=T[i+1];
				T[i+1]=tmp;
			}
		}
	}
}

void sudoku::afficheposibilite(){
	for (int i=0;i<N;i++){
		cout<<T[i].n<<" ";
	}
	cout<<endl;
}


bool sudoku::possible(int grilleSudoku[9][9], int ligne, int colonne, int numero)
{
    for(int i=0; i<=8;i++) //si numero est deja dans la ligne
    {
        if(grilleSudoku[ligne][i] == numero) return false;
    }
     for(int i=0; i<=8;i++) //si numero est deja dans la colonne
    {
        if(grilleSudoku[i][colonne] == numero) return false;
    }
    //si numero est deja dans le bloc
    int blocLigne=ligne-ligne%3;
    int blocColonne=colonne-colonne%3;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(grilleSudoku[i+blocLigne][j+blocColonne] == numero) return false;
        }
    }
    return true;
}

bool sudoku::backTracking(int grilleSudoku[9][9], int ligne, int colonne)
{
    if(ligne==8 && colonne==9) return true;
    if(colonne==9)
    {
        ligne+=1;
        colonne=0;
    }
    if(grilleSudoku[ligne][colonne]>0) return backTracking(grilleSudoku,ligne,colonne+1);
    for(int i =1; i<=9;i++)
    {
        if(possible(grilleSudoku,ligne,colonne,i))
        {
            grilleSudoku[ligne][colonne]=i;
            if(backTracking(grilleSudoku,ligne,colonne+1)) return true;
        }
        grilleSudoku[ligne][colonne]=0;
    }
    return false;
}
/*bool sudoku::backtracking(cellule *T,int k){
	//V1
	if (k==N+1) return true ;
	else {
		for (int j=1;j<=9;j++){
			if (!ligne[T[k].l][j-1] && !colonne[T[k].c][j-1] && !bloc[T[k].b][j-1]){
				int tmp = grille[T[k].l][T[k].c];
				grille[T[k].l][T[k].c]=j;
				if(backtracking(T,k+1)){
					
					return true;
				}
				grille[T[k].l][T[k].c]= tmp ;
			}
		}
	}
	return false ;
	
	/* /V2
	if (k==N+1) return true ;
	else {
		for (int j=1;j<=9;j++){
			if (!ligne[T[k].l][j-1] && !colonne[T[k].c][j-1] && !bloc[T[k].b][j-1]){
				ligne[T[k].l][j]=true ;
				colonne[T[k].c][j]=true;
				bloc[T[k].b][j]=true;
				
				if(backtracking(T,k+1)){
					grille[T[k].l][T[k].c]=j;
					return true;
				}
				ligne[T[k].l][j]=false ;
				colonne[T[k].c][j]=false;
				bloc[T[k].b][j]=false;
			}
		}
	}
	return false ;

}
*/
