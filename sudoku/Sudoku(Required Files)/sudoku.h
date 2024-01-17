/****************************************************************/
/* Auteur : S. Gueye						                    */
/* TP : Sudoku bactracking algorithm				            */
/* Date dernière maj : 24/11/2020				                */
/****************************************************************/

/****************************************************************/
/* Objectif : Classe représentant une cellule de la grille 
/****************************************************************/
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
	int ligne[9][9];
	int colonne[9][9];
	int bloc[9][9];
	int N;
	cellule T[81];
	

public : 
	sudoku(char filename[]);		// Lecture de la grille sudoku se trouvant dans le fichier filename
	void affichage();               // Affichage de la grille
	bool solution();                // Calcul de solution
	void testligne();
	void testcolonne();
	void testbloc();
	
	bool backTracking(int grilleSudoku[9][9], int ligne, int colonne);
	void trier();
	void afficheposibilite();
	bool possible(int grilleSudoku[9][9], int ligne, int colonne, int numero);
};



