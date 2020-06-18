#pragma once
#include "CCommande.h"
#include "CCapteur.h"
#include "CBatterie.h"
#include "CMesure.h"
#include "CMoteur.h"

/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpé par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : CRobiot.h
* PRESENTATION : Fichier header de la gestion globale du Robiot.
*
* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 16/06/20
*
***************************************************************/

class CRobiot
{
public:
	CRobiot();
	void Cheminer(int indexArbreSuivant);
	void Cheminer(coordonnees pointDestination);
	int algoDisjkra(coordonnees pointEntree, coordonnees pointSortie);
	void Mesurer();

	int NombreArbre();

private:
	CCapteur m_capteurRobiot;
	CCompas m_compasRobiot;
	CBatterie m_batterieRobiot;
	CMesure m_mesureRobiot;
	CMoteur m_moteurRobiot;
	CCommande m_commandeRobiot;
};

