#include <iostream>

using namespace std;

#include "sudoku.h"

/************************************************/
/* Programme principal				*/
/* argc : nombre d'arguments à l'appel du 	*/
/* programme exécutable				*/
/* argv : Liste des arguments			*/
/************************************************/
int main(int argc,char** argv)
{	
	if(argc < 2)
		cout << "Nombre d'arguments insuffisants" << endl;
	else{
		sudoku sudo(argv[1]);
		sudo.affichage();
		cout << "Solution de la grille du fichier" << endl;
		sudo.solution();
		sudo.affichage();		
		sudo.testligne();
		sudo.testcolonne();
		sudo.testbloc();
		//sudo.trier();
		sudo.afficheposibilite();
	}

	return(1);
}
