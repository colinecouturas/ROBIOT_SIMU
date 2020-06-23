/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpé par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : CCommande.cpp
* PRESENTATION : Fichier source de la sélection des arbres à controller.
*
* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 16/06/20
*
***************************************************************/

#include "pch.h"
#include "CCommande.h"

/**************************************************************
*
* METHODE : CCommande::getCoordonnees(int iNumero)
* PRESENTATION : Récupération d'un couple de coordonnées dans 
*                le tableau tabCoordonees.
*
* ENTREE :
*	int iNumero : indice du tableau correspondant au couple de 
*                 coordonnées que l'on veut récupérer.
* 
* SORTIE :
* 	coordonnees : couple de coordonnées que l'on veut récupérer.
* 
***************************************************************/

coordonnees CCommande::getCoordonnees(int iNumero)
{
	if (iNumero < tabCoordonnees.size()) {
		return (tabCoordonnees[iNumero]);
	} else {
		//OutputDebugString("L'indice du tableau est trop grand.");
		//return 0;
	}

} /* getCoordonnees */

/**************************************************************
*
* METHODE : CCommande::NombreArbre()
* PRESENTATION : Retourne le nombre d'arbre que le Robiot a à 
*                mesurer sur la cartographie.
*
* SORTIE : 
* 	int : nombre d'arbres.
* 
***************************************************************/

int CCommande::NombreArbre()
{
	return (tabCoordonnees.size());

} /* NombreArbre */

/**************************************************************
*
* METHODE : CCommande::lireTableau()
* PRESENTATION : Remplissage du tableau tabCoordonnees en 
*                fonction des coordonnées du fichier LISTE DE 
*                CONTROLE.
*
* SORTIE :
* 	int : retourne 0 en cas de succès.
* 
***************************************************************/

int CCommande::LireTableau(char* nomListe)
{
	ifstream file;

	/* Ouverture du fichier listant les arbres à mesurer. */
	file.open(nomListe);
	if (file) {
		while(!file.eof()){
			coordonnees point;
			file >> point.x;
			file >> point.y;
			tabCoordonnees.push_back(point);
		}
		file.close();
	}
	else {
		cout << "Probleme ouverture du fichier." << endl;
		return (1);
	}
	return (0);

} /* LireTableau */


