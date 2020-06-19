#include "CRobiot.h"
#include <math.h>

/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpé par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : CRobiot.h
* PRESENTATION : Fichier source de la gestion globale du Robiot.
*
* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 18/06/20
*
***************************************************************/

int main()
{
	/* Le robot ouvre la liste des coordonnées. */
	/* Utilisation de l'algorithme de djiktra sur le tableau pour trouver le chemin le plus court. */

	int i = 0;
	CRobiot petitRobiot = CRobiot();
	coordonnees pointInitial = { 0, 0 };

	for (i = 0; i < petitRobiot.NombreArbre(); i++) {
		
		cout << "On se dirige vers l'arbre numero " << i+1 <<  endl;
		petitRobiot.Cheminer(i);
		cout << "On mesure l'arbre " << i+1  << endl;
		petitRobiot.Mesurer();
		//revenir au point de départ
	}
	petitRobiot.Cheminer(pointInitial);
	cout << "c'est fini ! " << endl;
	cout << "Le petit Robiot a utilise " << petitRobiot.BatterieUtilisee() << " J pour mesurer les arbres de ce terrain." << endl;
	int tailleTerrain = petitRobiot.LargeurTerrain() * petitRobiot.LongueurTerrain();
	cout << "Le terrain mesurait " << tailleTerrain << " m carre" << endl;
	
	return (0);

} /* main */

/**************************************************************
*
* METHODE : CRobiot::CRobiot()
* PRESENTATION : Constructeur de la classe CRobiot.
*
***************************************************************/

CRobiot::CRobiot()
{
	m_commandeRobiot.LireTableau();
	m_capteurRobiot.LireCartographie();
	m_mesureRobiot = CMesure();
	m_moteurRobiot = CMoteur();
	m_batterieRobiot = CBatterie();
	m_compasRobiot = CCompas();

} /* CRobiot */


/**************************************************************
*
* METHODE : CRobiot::Cheminer(int indexArbreSuivant)
* PRESENTATION : Déplacement du Robiot. Cheminement entre sa position courant et la position du prochain arbre.
*
* ENTREE : 
* 	int indexArbreSuivant : indice des coordonnées du prochain arbre.
* 
***************************************************************/
/*
	* INFO CLIENT :
	* 1 sur carte = 10m en réel
	*/


void CRobiot::Cheminer(int indexArbreSuivant)
{	
	coordonnees pointCourant = m_compasRobiot.getCompas();

	/* Calclul de la disance (Dijkstra). */
	int distance= algoDisjkra(m_compasRobiot.getCompas(), m_commandeRobiot.getCoordonnees(indexArbreSuivant));

	/* Allumage du moteur. */
	m_moteurRobiot.setMoteur(true);

	/* Consommation de la batterie. */
		//Carte mère ARM dont la consommation moyenne en fonctionnement est de 12.5 Watts.
		//Le Moteur permet le déplacement du ROBIOT à une vitesse 0.42 m.s-1
		//La puissance moyenne demandée par le moteur d’une roue est de 14,0 Watts = J/s.
	int puissanceNecessaire = ((14*2)+12.5) * (distance / 0.42) ; //J
	m_batterieRobiot.addBatterie(puissanceNecessaire);


	/* Mise à jour des coordonnées du point courant une fois arrivé. */
	m_compasRobiot.setCompas(m_commandeRobiot.getCoordonnees(indexArbreSuivant));

	/* Extinction du moteur. */
	m_moteurRobiot.setMoteur(false);

} /* Cheminer */

void CRobiot::Cheminer(coordonnees pointDestination)
{
	coordonnees pointCourant = m_compasRobiot.getCompas();

	/* Calclul de la disance (Dijkstra). */
	int distance = algoDisjkra(m_compasRobiot.getCompas(), pointDestination);
	//int distance = algoDisjkra(point entree , point sortie);

	/* Allumage du moteur. */
	m_moteurRobiot.setMoteur(true);

	/* Consommation de la batterie. */
		//Carte mère ARM dont la consommation moyenne en fonctionnement est de 12.5 Watts.
		//Le Moteur permet le déplacement du ROBIOT à une vitesse 0.42 m.s-1
		//La puissance moyenne demandée par le moteur d’une roue est de 14,0 Watts = J/s.
	int puissanceNecessaire = ((14 * 2) + 12.5) * (distance / 0.42); //J
	m_batterieRobiot.addBatterie(puissanceNecessaire);


	/* Mise à jour des coordonnées du point courant une fois arrivé. */
	m_compasRobiot.setCompas(pointDestination);

	/* Extinction du moteur. */
	m_moteurRobiot.setMoteur(false);

} /* Cheminer */

int CRobiot::algoDisjkra(coordonnees pointEntree, coordonnees pointSortie)
{
	int distance = sqrt(pow((pointSortie.y - pointEntree.y), 2) - pow((pointSortie.x - pointEntree.x), 2));
	return distance;
}

/**************************************************************
*
* METHODE : CRobiot::Mesurer()
* PRESENTATION : Mesure de l'arbre courant.
*
***************************************************************/
void CRobiot::Mesurer()
{
	m_mesureRobiot.setMesure(true);

	// Carte mère ARM : 12.5 Watts.
	// Système de mesure : 30,0 Watts.
	// Durée de mesure : 5 mins
	int puissanceNecessaire = (30 + 12.5) * 5 * 60; //J
	m_batterieRobiot.addBatterie(puissanceNecessaire);

	m_mesureRobiot.setMesure(false);

} /* Mesurer */

/**************************************************************
*
* METHODE : CRobiot::NombreArbre()
* PRESENTATION : Retourne le nombre d'arbre que le Robiot a à mesurer sur la cartographie.
*
***************************************************************/

int CRobiot::NombreArbre()
{
	return m_commandeRobiot.NombreArbre();

} /* NombreArbre */

int CRobiot::BatterieUtilisee()
{
	return m_batterieRobiot.getBatterie();
}

int CRobiot::LargeurTerrain()
{
	return m_capteurRobiot.getLargeurTerrain();
}

int CRobiot::LongueurTerrain()
{
	return m_capteurRobiot.getLongueurTerrain();
}

