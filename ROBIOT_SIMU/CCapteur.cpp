#include "CCapteur.h"
#include <iostream>

/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpé par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : CCapteur.cpp
* PRESENTATION : Fichier source de la gestion des capteurs de signaux balise (Bordures de terrain, Obstacles, Arbres).

* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 16/06/20
*
***************************************************************/

/* ouvre le fichier de cartographie*/

/* on vient me demander si j'ai qqch a cet endroit*/

/* faire un tableau avec les coordonnées des obstacles.*/
using namespace std;

/**************************************************************
* METHODE : CCapteur::LireCartographie()
* PRESENTATION : Récupération d'un couple de coordonnées d'un obstacle dans le tableau tabCoordoneesObstacle.
*
* SORTIE :
* 	int : retourne 0 en cas de succès.
***************************************************************/

int CCapteur::LireCartographie()
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
		return (1);
	}
	file.close();
	return (0);
} /* LireCartographie */
