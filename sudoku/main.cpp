#include <iostream>

using namespace std;

#include "sudoku.h"

/************************************************/
/* Programme principal				*/
/* argc : nombre d'arguments à l'appel du 	*/
/* programme exécutable				*/
/* argv : Liste des arguments			*/
/************************************************/
int main(int argc,char** argv) //.\main entree1.txt
{	
	if(argc < 2)
		cout << "Nombre d'arguments insuffisants" << endl;
	else{
		sudoku sudo(argv[1]);
		sudo.affichage();
		cout << "Solution de la grille du fichier" << endl;
		sudo.solution();
		sudo.affichage();
		sudo.backtracking();
		sudo.affichageL();		
	}

	return(1);
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
*/