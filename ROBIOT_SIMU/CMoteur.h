#pragma once
class CMoteur
{

public:
	CMoteur() {
		m_bMoteur = false;
	}

	bool getMoteur() { return m_bMoteur; }
	void setMoteur(bool bMoteur) { m_bMoteur = bMoteur; }

private:
	bool m_bMoteur;
};

