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

#pragma once
#include "CCommande.h"
#include "CCapteur.h"
#include "CBatterie.h"
#include "CMesure.h"
#include "CMoteur.h"

class CRobiot
{
public:
	CRobiot();
	int Cheminer(int indexArbreSuivant);
	int Cheminer(coordonnees pointDestination);
	int Disjkra(coordonnees pointEntree, coordonnees pointSortie);
	void Mesurer();
	void setPosition(coordonnees positionActuelle);

	
	CCapteur getRobiotCapteur();
	CCompas getRobiotCompas();
	CBatterie getRobiotBatterie();
	CMesure getRobiotMesure();
	CMoteur getRobiotMoteur();
	CCommande getRobiotCommande();


private:
	CCapteur m_capteurRobiot;
	CCompas m_compasRobiot;
	CBatterie m_batterieRobiot;
	CMesure m_mesureRobiot;
	CMoteur m_moteurRobiot;
	CCommande m_commandeRobiot;
};

