#pragma once

typedef struct {
	int x;
	int y;
} coordonnees;

class CCompas
{
public: 

	CCompas() {
		m_cPoint = coordonnees{ 0,0 };
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


