#include "pch.h"
#include "CCapteur.h"
#include <iostream>

/**************************************************************
*
* Reproduction et diffusion interdites.
* Developp� par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : CCapteur.cpp
* PRESENTATION : Fichier source de la gestion des capteurs de signaux balise (Bordures de terrain, Obstacles, Arbres).

* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 16/06/20
*
***************************************************************/

using namespace std;

/**************************************************************
*
* METHODE : CCapteur::LireCartographie()
* PRESENTATION : R�cup�ration d'un couple de coordonn�es d'un obstacle dans le tableau tabCoordoneesObstacle.
*
* SORTIE :
* 	int : retourne 0 en cas de succ�s.
* 
***************************************************************/

int CCapteur::LireCartographie(string nomCarto)
{
	ifstream file;
	int x = 0;
	int y = 0;
	bool isSet = false;
	char c;

	/* Ouverture du fichier de cartographie. */
	file.open(nomCarto);
	if (file) {
		do {
			file.get(c);
			if (c == '\n') {
				y += 1;
				if (isSet == false) {
					m_ilargeurTerrain = x;
					isSet = true;
				}
				x = 0;
			}
			else if (c != ' ') {
				/* Remplissage d'un premier tableau rassemblant l'ensemble des �l�ments de la carte. */
				tabCoordonneesObjets.push_back(coordonnees{ x, y });
				if (c == 'X') {
					/* Remplissage d'un tableau d'obstacles � partir de la cartographie. */
					tabCoordonneesObstacles.push_back(coordonnees{ x, y });
				}
				else if (c == 'O') {
					/* Remplissage d'un tableau d'arbres � partir de la cartographie. */
					tabCoordonneesArbres.push_back(coordonnees{ x, y });
				}
				x += 1;
			}
			else x += 1;
			
		} while (!file.eof());

		/* La longueur du terrain prend y+1 car on n'a pas de '\n' sur la derni�re ligne. */
		m_ilongueurTerrain = y+1;
		 
	}
	else {
		cout << "Probleme d'ouverture du fichier." << endl;
		return (1);
	}
	file.close();
	return (0);

} /* LireCartographie */

/**************************************************************
*
* METHODE : CCapteur::getLongueurTerrain()
* PRESENTATION : R�cup�ration de la longueur du terrain.
*
* SORTIE :
* 	int : longueur du terrain.
* 
***************************************************************/

int CCapteur::getLongueurTerrain()
{
	return (m_ilongueurTerrain);

} /* getLongueurTerrain */

/**************************************************************
*
* METHODE : CCapteur::getLargeurTerrain()
* PRESENTATION : R�cup�ration de la largeur du terrain.
*
* SORTIE :
* 	int : largeur du terrain.
* 
***************************************************************/

int CCapteur::getLargeurTerrain()
{
	return (m_ilargeurTerrain);

} /* getLargeurTerrain */
