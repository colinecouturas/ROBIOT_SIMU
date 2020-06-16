#pragma once

/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpé par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : CCapteur.h
* PRESENTATION : Fichier header de la gestion des capteurs de signaux balise (Bordures de terrain, Obstacles, Arbres).
*
* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 16/06/20
*
***************************************************************/

#include <cstdio>
#include <fstream>
#include <vector>
#include "CCompas.h"

class CCapteur
{
public:
	CCapteur() {
		tabCoordonneesObstacles.clear();
	}

	int LireCartographie();

private:

	std::vector<coordonnees> tabCoordonneesObstacles;

	enum {
		bordure =1,
		obstacle,
		arbre
	};
};

