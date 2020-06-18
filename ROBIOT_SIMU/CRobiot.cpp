#include "CRobiot.h"

/**************************************************************
*
* Reproduction et diffusion interdites.
* Developp� par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
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
	/* Le robot ouvre la liste des coordonn�es. */
	/* Utilisation de l'algorithme de djiktra sur le tableau pour trouver le chemin le plus court. */

	int i = 0;
	CRobiot petitRobiot = CRobiot();

	for (i = 0; i < petitRobiot.NombreArbre(); i++) {
		petitRobiot.Cheminer(i);
		petitRobiot.Mesurer();
	}
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
* PRESENTATION : D�placement du Robiot. Cheminement entre sa position courant et la position du prochain arbre.
*
* ENTREE : 
* 	int indexArbreSuivant : indice des coordonn�es du prochain arbre.
* 
***************************************************************/

void CRobiot::Cheminer(int indexArbreSuivant)
{	
	coordonnees pointCourant = m_compasRobiot.getCompas();

	/* Calclul de la disance (Dijkstra). */

	/* Allumage du moteur. */
	m_moteurRobiot.setMoteur(true);

	/* Consommation de la batterie. */
		// carte m�re ARM dont la consommation moyenne en fonctionnement est de 12.5 Watts.
		//Le Moteur permet le d�placement du ROBIOT � une vitesse 0.42 m.s-1
		//La puissance moyenne demand�e par le moteur d�une roue est de 14,0 Watts.


	/*
	 * INFO CLIENT :
	 * 1 sur carte = 10m en r�el
	 * /

	/* Mise � jour des coordonn�es du point courant une fois arriv�. */
	m_compasRobiot.setCompas(m_commandeRobiot.getCoordonnees(indexArbreSuivant));

	/* Extinction du moteur. */
	m_moteurRobiot.setMoteur(false);

} /* Cheminer */

/**************************************************************
*
* METHODE : CRobiot::Mesurer()
* PRESENTATION : Mesure de l'arbre courant.
*
***************************************************************/

void CRobiot::Mesurer()
{
	// carte m�re ARM dont la consommation moyenne en fonctionnement est de 12.5 Watts.
	// faire diminuer batteire, attendre '5mins'
	//puissance moyenne consomm�e par le syst�me de mesure est de 30,0 Watts.

	m_mesureRobiot.setMesure(true);



	m_mesureRobiot.setMesure(false);

} /* Mesurer */

/**************************************************************
*
* METHODE : CRobiot::NombreArbre()
* PRESENTATION : Retourne le nombre d'arbre que le Robiot a � mesurer sur la cartographie.
*
***************************************************************/

int CRobiot::NombreArbre()
{
	return m_commandeRobiot.NombreArbre();

} /* NombreArbre */

