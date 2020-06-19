#pragma once

/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpé par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : CMoteur.h
* PRESENTATION : Fichier header de la gestion du moteur du Robiot.
*
* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 16/06/20
*
***************************************************************/

class CMoteur
{
public:
	CMoteur() {
		m_bMoteur = false;
	}

	bool getMoteur() {
		return m_bMoteur;
	}

	void setMoteur(bool bMoteur) {
		m_bMoteur = bMoteur;
	}

private:
	bool m_bMoteur;
};

