#include <iostream>
#include "FonctionJeux.h"
using namespace std;
/**
 * @brief Programme d'execution du jeu 
 */

int main(int argc, char* argv[]) {
	Jeux j;
	
	if (verif(argv[1]) == 1)
		return 1;

	intialiser_struct(j, argv[1]);

	partie(j, argv[1]);

	desallouer(j);

	return 0;

}
