#include "CCapteur.h"
#include <iostream>
/* ouvre le fichier de cartographie*/

/* on vient me demander si j'ai qqch a cet endroit*/

/* faire un tableau avec les coordonnées des obstacles.*/
using namespace std;

int CCapteur::lireCartographie()
{
	ifstream file;
	file.open("CARTOGRAPHIE");
	/*if (file) {
		do {
			for (int i = 0; i < tab_coordonnees.size(); i++) {
				coordonnees point;
				file >> point.x;
				file >> point.y;
				tab_coordonnees.push_back(point);
			}
		} while (!file.eof());
	}
	else {
		cout << "Probleme ouverture du fichier." << endl;
	}*/
	file.close();
	return 0;
}
