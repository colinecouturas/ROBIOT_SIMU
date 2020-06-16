#pragma once
class CCompas
{
	CCompas() {
		m_cPoint = coordonnees{ 0,0 };
	}

	void setCompas(coordonnees point) {
		m_cPoint = point;
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

typedef struct {
	int x;
	int y;
} coordonnees;