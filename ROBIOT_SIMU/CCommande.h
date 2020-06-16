#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "CCompas.h"
using namespace std;

class CCommande
{
	
public:
	CCommande() { ; };

	coordonnees getCoordonnees(int iNumero);

	void lireTableau();

private:
	vector<coordonnees> tabCoordonnees;
};

