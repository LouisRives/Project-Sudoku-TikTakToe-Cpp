#include <fstream>
#include <iostream>
#include <iomanip>

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
}


/****************************************/
/* Objectif : Construteur avec argument 
permettant la création d'une grille à partir d'un 
fichier.
/****************************************/
sudoku::sudoku(char filename[])
{
	ifstream file;
	file.open(filename, std::ifstream::in);
	int nombre;

    while(!file.eof()){
		//remplir le tableau avec c;
		for (int ligneT=0; ligneT<9; ligneT++){
			for (int colT=0; colT<9; colT++){
				ligne[ligneT][colT]=false;
				colonne[ligneT][colT]=false;
				bloc[3*(ligneT/3)+(colT/3)][colT]=false;
			}
		}
		for (int ligneT=0; ligneT<9; ligneT++){
			for (int colT=0; colT<9; colT++){
				file>>grille[ligneT][colT];
				nombre = grille[ligneT][colT];
				if (nombre == 0){ // si la case est vide : 
					cellule S(ligneT,colT);
					T[nombre]=S;
					nombre++;
				}
				else { // true si la case est 
					ligne[ligneT][colT]=true;
					colonne[ligneT][colT]=true;
					bloc[3*(ligneT/3)+(colT/3)][colT]=true;
				}
			}
		}
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

void sudoku::affichageL()
{
	cout << setw(3) << "-" << "------------------------------------" << endl;
	for(int i = 0; i < 9; i++){
		if((i == 3) || (i == 6))
			cout << setw(3) << "-" << "------------------------------------" << endl;
		cout << setw(3) << "|";		
		for(int j = 0; j < 8; j++){
			if((j == 3) || (j == 6))
				cout << setw(3) << "|" << setw(3) << colonne[i][j];
			else
				cout << setw(3) << colonne[i][j];
		}
		cout << setw(3) << colonne[i][8] << setw(3)<<  "|" << endl;
	}
	cout << setw(3) << "-" << "------------------------------------" << endl;
}

/****************************************/
/* Objectif : Détermination d'une solution de la grilleées.
La méthode renvoie vrai si une solution a été trouvée, 0 sinon
/****************************************/
bool sudoku::solution()
{
    // A FAIRE !!! //
	return(true);
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

bool sudoku::backtracking(int grilleSudoku[9][9], int ligne, int colonne)
{
    if(ligne==8 && colonne==9) return true;
    if(colonne==9)
    {
        ligne+=1;
        colonne=0;
    }
    if(grilleSudoku[ligne][colonne]>0) return backtracking(grilleSudoku,ligne,colonne+1);
    for(int i =1; i<=9;i++)
    {
        if(possible(grilleSudoku,ligne,colonne,i))
        {
            grilleSudoku[ligne][colonne]=i;
            if(backtracking(grilleSudoku,ligne,colonne+1)) return true;
        }
        grilleSudoku[ligne][colonne]=0;
    }
    return false;
}


/*

fonction Backtracking : contient un tableau de celulule contenant toutes les cellules vides et la taille de l'arbre k, permet donc une récursivité sur k, si k= le nombre de case vide (N), alors on est bon)

bool backtracking(cellule *T, int k){
	if k=N return true;
	else {
		for (int r=1; r<=9;r++){
			if (not ligne[T[k].l][r-1] and not colonne[T[k].c][r-1] and not bloc[T[k].b][r-1]){
				//ligne, colonne, bloc .... =1;
				if(BT(T,k+1)){
					Grille[T[k].l][T[k].c]=r;
					return(true);
				}
				else //remettre les ligne colonnes, bloc = false... car echec
			}
		//return false ??
		}
	}
}

void soduku::mettre_a_jour()
{
	for(h=0;h<N;h++)
	{
		T[h].n=0;
		for(r=1;r<10;r++){
			if(not ligne[T[h].l][r-1] and not colonne[T[h].c][r-1] and not colonne[T[h].b][r-1]){
				(T[h].n)++;
				
			}
		}
	}
}


sohtica (cellule *T, int h){
	if k=N return true;
	pour chaque chiffre c!=0
		si c est possible 
			if(!ligne[T[h].l][c-1])
				ligne colonne bloc....
			if(solution(T,l+1)){
				grille[T[h].l][T[h].c]=c;
				return true;
			}
	
}

void trier (cellule *T, int N)
{
	for(int F=N-1; F>0; F--){
		for (int i=0;i<F;i++){
			
		}
	}
}

*/