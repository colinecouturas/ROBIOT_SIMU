#pragma once
#include <iostream>
using namespace std;

class CCommande
{
	CCommande();

	coordonnees getCoordonnees(int iNumero);

	void lireTableau();

private:
	coordonnees tab_coordonnees[];
};

