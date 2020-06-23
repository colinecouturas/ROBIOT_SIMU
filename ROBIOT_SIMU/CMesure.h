/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpé par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : CMesure.h
* PRESENTATION : Fichier header permettant de savoir si le Robiot est en train de réaliser des mesures.
*
* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 16/06/20
*
***************************************************************/

#pragma once

class CMesure
{
	/* INFO CLIENT :
	 * Le cycle de mesures prend une durée moyenne de cinq minutes par arbre 
	 * et la puissance moyenne consommée par le système de mesure est de 30,0 Watts. */

public:
	CMesure() {
		m_bMesure = false;
	}

	bool getMesure() {
		return m_bMesure;
	}

	void setMesure(bool bMesure) {
		m_bMesure = bMesure;
	}

private:
	bool m_bMesure;
};

