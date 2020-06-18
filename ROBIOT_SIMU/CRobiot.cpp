#include "CRobiot.h"


int main() {
	/*le robot ouvre la liste des coordonn�es*/
	/*applique l'algo de djiktra sur le tableau pour trouver le chemin le plus court*/
	int i = 0;
	CRobiot petitRobiot = CRobiot();

	for (i = 0; i < petitRobiot.NombreArbre(); i++) {
		petitRobiot.Cheminer(i);
		petitRobiot.Mesurer();
	}
	return 0;
}

CRobiot::CRobiot()
{
	m_commandeRobiot.LireTableau();
	m_capteurRobiot.LireCartographie();
	m_mesureRobiot = CMesure();
	m_moteurRobiot = CMoteur();
	m_batterieRobiot = CBatterie();
	m_compasRobiot = CCompas();
}

void CRobiot::Cheminer(int indexArbreSuivant)
{	
	//calcule djiskra
	coordonnees pointCourant = m_compasRobiot.getCompas();
	//allumer moteur 
	m_moteurRobiot.setMoteur(true);

	//consommation batterie
		// carte m�re ARM dont la consommation moyenne en fonctionnement est de 12.5 Watts.
		//Le Moteur permet le d�placement du ROBIOT � une vitesse 0.42 m.s-1
		//La puissance moyenne demand�e par le moteur d�une roue est de 14,0 Watts.


	// 1 sur carte = 10m en r�el

	//Mettre a jour les coordonnees du point courant une fois arriv�
	m_compasRobiot.setCompas(m_commandeRobiot.getCoordonnees(indexArbreSuivant));

	//eteindre moteur
	m_moteurRobiot.setMoteur(false);
}

void CRobiot::Mesurer()
{
	// carte m�re ARM dont la consommation moyenne en fonctionnement est de 12.5 Watts.
	// faire diminuer batteire, attendre '5mins'
	//puissance moyenne consomm�e par le syst�me de mesure est de 30,0 Watts.
	m_mesureRobiot.setMesure(true);



	m_mesureRobiot.setMesure(false);

}

int CRobiot::NombreArbre()
{
	return m_commandeRobiot.NombreArbre();
}

