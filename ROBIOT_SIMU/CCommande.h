#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "CCompas.h"
using namespace std;

/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpé par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : CCommande.h
* PRESENTATION : Fichier header de la sélection des arbres à controller.
*
* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 16/06/20
*
***************************************************************/

class CCommande
{
public:
	CCommande() { ; };

	coordonnees getCoordonnees(int iNumero);
	int NombreArbre();
	int LireTableau();

private:
	vector<coordonnees> tabCoordonnees;
};

