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

class CCapteur
{
	
public:
	int lireCartographie();

private:


	enum {
		bordure =1,
		obstacle,
		arbre
	};
};

