/****************************************************************/
/* Auteur : S. Gueye						                    */
/* TP : Sudoku bactracking algorithm				            */
/* Date dernière maj : 24/11/2020				                */
/****************************************************************/

/****************************************************************/
/* Objectif : Classe représentant une cellule de la grille 
/****************************************************************/

#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include <iostream>
using namespace std;

class cellule
{
	public :
	int l; 			        // Numéro de ligne
	int c; 			        // Numéro de colonne
	int b; 			        // Numéro du bloc où se situe la cellule (l,c)
	int n;			        // Nombre de chiffres qu'il est possible initialement d'utiliser sur la cellule
	cellule(int i=0, int j=0);  // Construit la cellule de numéro de ligne i et colonne j
};


/****************************************************************/
/* Objectif : Classe permettant de lire une grille sudoku et de la résoudre
/****************************************************************/
class sudoku{
	int grille[9][9];			    // La grille
	bool ligne[9][9];				// Les lignes
	bool colonne[9][9];				// Les colonnes
	bool bloc[9][9];				// Les blocs
	int N;
	cellule T[81];					// Tableau de cases

public : 
	sudoku(char filename[]);		// Lecture de la grille sudoku se trouvant dans le fichier filename
	void affichage();               // Affichage de la grille
	void affichageL();   			// Affichage de case vide ou pleine
	bool solution();                // Calcul de solution
	bool possible(int grilleSudoku[9][9], int ligne, int colonne, int numero);
	bool backtracking(int grilleSudoku[9][9], int ligne, int colonne);

};

#endif

