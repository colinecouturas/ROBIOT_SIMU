#pragma once

/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpé par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : CCompas.h
* PRESENTATION : Fichier header de la récupération de la position du Robiot.
*
* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 16/06/20
*
***************************************************************/

typedef struct {
	int x;
	int y;
} coordonnees;

class CCompas
{
public: 
	CCompas() {
		m_cPoint = coordonnees{0,0};
	}

	void setCompas(coordonnees point) {
		m_cPoint.x = point.x;
		m_cPoint.y = point.y;
	}

	void setCompas(int iX, int iY) {
		m_cPoint.x = iX;
		m_cPoint.y = iY;
	}

	coordonnees getCompas() {
		return m_cPoint;
	}

	int getCompasX() {
		return m_cPoint.x;
	}

	int getCompasY() {
		return m_cPoint.y;
	}

private:
	coordonnees m_cPoint;
};


