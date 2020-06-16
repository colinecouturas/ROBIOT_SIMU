#include "CCapteur.h"
#include <iostream>
/* ouvre le fichier de cartographie*/

/* on vient me demander si j'ai qqch a cet endroit*/

/* faire un tableau avec les coordonnées des obstacles.*/
using namespace std;

int CCapteur::lireCartographie()
{
	FILE* pFile;
	pFile = fopen("CARTOGRPAHIE","r");
	if (pFile == NULL) {
		cout << "Probleme ouverture du fichier." << endl;
	}
	else {

	}

	return 0;
}
