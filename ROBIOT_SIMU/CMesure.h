#pragma once
class CMesure
{
	/*Le cycle de mesures prend une dur�e moyenne de cinq minutes par arbre 
	et la puissance moyenne consomm�e par le syst�me de mesure est de 30,0 Watts.*/

public:
	CMesure() {
		m_bMesure = false;
	}

	bool getMesure() { return m_bMesure; }
	void setMesure(bool bMesure) { m_bMesure = bMesure; }

private:
	bool m_bMesure;
};

