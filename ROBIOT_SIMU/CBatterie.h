#pragma once
class CBatterie
{

public:
	CBatterie() {
		m_iBatterie = 100;
	}

	int getBatterie() { return m_iBatterie; }
	void setBatterie(int iBatterie) { m_iBatterie = iBatterie; }

private : 
	int m_iBatterie; 
};

