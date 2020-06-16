#include "CCommande.h"

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

/**************************************************************
* METHODE : CCommande::getCoordonnees(int iNumero)
* PRESENTATION : Récupération d'un couple de coordonnées dans le tableau tabCoordonees.
*
* ENTREE :
*	int iNumero : indice du tableau correspondant au couple de coordonnées que l'on veut récupérer.
* 
* SORTIE :
* 	coordonnees : couple de coordonnées que l'on veut récupérer.
***************************************************************/

coordonnees CCommande::getCoordonnees(int iNumero)
{
	if (iNumero < tabCoordonnees.size()) {
		return tabCoordonnees[iNumero];
	}
} /* getCoordonnees */

/**************************************************************
* METHODE : CCommande::lireTableau()
* PRESENTATION : Remplissage du tableau tabCoordonnees en fonction des coordonnées du fichier LISTE DE CONTROLE.
*
* SORTIE :
* 	int : retourne 0 en cas de succès.
***************************************************************/
int CCommande::LireTableau()
{
	ifstream file;
	file.open("LISTE DE CONTROLE");
	if (file) {
		do{
			for (int i = 0; i < tabCoordonnees.size(); i++) {
				coordonnees point;
				file >> point.x;
				file >> point.y;
				tabCoordonnees.push_back(point);
			}
		}while(!file.eof());
	}
	else {
		cout << "Probleme ouverture du fichier." << endl;
		return (1);
	}
	file.close();
	return (0);
} /* LireTableau */


