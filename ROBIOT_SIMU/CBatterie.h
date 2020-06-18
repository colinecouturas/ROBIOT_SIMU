#pragma once

/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpé par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : CCommande.h
* PRESENTATION : Fichier header de la gestion de la batterie.
*
* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 16/06/20
*
***************************************************************/

class CBatterie
{
public:
	CBatterie() {
		m_iBatterie = 0;
	}

	int getBatterie() { return m_iBatterie; }
	void setBatterie(int iBatterie) { m_iBatterie = iBatterie; }
	void addBatterie(int iBatterie) { m_iBatterie += iBatterie; }

private : 
	int m_iBatterie; 
};

