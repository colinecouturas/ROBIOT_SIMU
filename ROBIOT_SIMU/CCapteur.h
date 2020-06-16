#pragma once
/**************************************************************
/** 
* Developpe par INSA Rennes  5 CDTI : CCOUTURAS ABODIN 
* Projet ROBIOT 
* SOURCE : CCapteur.h 
* PRESENTATION : Capteur de signaux balise(Bordures de terrain, Obstacles, Arbres)
* AUTEUR : cct, abd
* DATE : 16/06/2020
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

	int lireCartographie();

private:

	std::vector<coordonnees> tabCoordonneesObstacles;

	enum {
		bordure =1,
		obstacle,
		arbre
	};
};

