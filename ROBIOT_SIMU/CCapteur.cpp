#include "CCapteur.h"
#include <iostream>
/* ouvre le fichier de cartographie*/

/* on vient me demander si j'ai qqch a cet endroit*/

/* faire un tableau avec les coordonnées des obstacles.*/
using namespace std;

int CCapteur::lireCartographie()
{
	ifstream file;
	int x = 0;
	int y = 0;
	file.open("CARTOGRAPHIE.txt");
	if (file) {
		do {
			char c;
			file.get(c);
			if (c == '\0'){
					y += 1;
					x = 0;
			}
			else if (c != ' ' ) {
				tabCoordonneesObstacles.push_back(coordonnees{ x, y });
				x = +1;
				
			}			
			else x = +1;
			
		} while (!file.eof());
	}
	else {
		cout << "Probleme ouverture du fichier." << endl;
		return 1;
	}
	file.close();
	return 0;
}
