#include "CRobiot.h"
#include <math.h>

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

/**************************************************************
*
* METHODE : main()
* PRESENTATION : Fonction principale.
* Cr�ation d'un Robiot qui parcours une carte sur laquelle se trouvent des arbres et des obstacles.
* Le Robiot doit mesurer certains des arbres, et informer quant � la batterie qu'il a consomm� pour se faire.
*
* SORTIE :
* 	int : retourne 0 en cas de succ�s.
* 
***************************************************************/

int main()
{
	/* Le robot ouvre la liste des coordonn�es. */
	/* Utilisation de l'algorithme de djiktra sur le tableau pour trouver le chemin le plus court. */

	int i = 0;

	/* D�finition d'un Robiot. */
	CRobiot petitRobiot = CRobiot();

	/* D�finition du point de d�part, auquel on va revenir � la fin. */
	coordonnees pointInitial = { 0, 0 };

	for (i = 0; i < petitRobiot.NombreArbre(); i++) {
		cout << "On se dirige vers l'arbre numero " << i+1 <<  endl;
		petitRobiot.Cheminer(i);
		cout << "On mesure l'arbre " << i+1  << endl;
		petitRobiot.Mesurer();
	}

	/* On revient au point de depart. */
	petitRobiot.Cheminer(pointInitial);

	cout << "C'est fini ! " << endl;
	cout << "Le petit Robiot a utilise " << petitRobiot.BatterieUtilisee() << " J pour mesurer les arbres de ce terrain." << endl;
	int tailleTerrain = petitRobiot.LargeurTerrain() * petitRobiot.LongueurTerrain();
	cout << "Le terrain mesurait " << tailleTerrain << " m carre." << endl;

	return (0);

} /* main */

/**************************************************************
*
* METHODE : CRobiot::CRobiot()
* PRESENTATION : Constructeur de la classe CRobiot.
* Dans ce constructeur on associe tous les param�tres connus avec un Robiot.
* En particulier, on va lire les fichiers d'entr�e.
* Le Robiot connait donc la position des obstacles, et des arbres � aller mesurer.
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
	int distance = algoDisjkra(m_compasRobiot.getCompas(), m_commandeRobiot.getCoordonnees(indexArbreSuivant));

	/* INFO CLIENT :
	 * 1 sur carte = 10 m en r�el. */
	distance = distance * 10;

	/* Allumage du moteur. */
	m_moteurRobiot.setMoteur(true);

	/* Consommation de la batterie :
	 * Carte m�re ARM : 12.5 Watts.
	 * Vitesse : 0.42 m.
	 * Moteur d'une roue : 14,0 Watts. */

	/* Calcul de la puissance en Joule. */
	int puissanceNecessaire = ((14 * 2) + 12.5) * (distance / 0.42); //J

	/* Incr�mentation de la batterie pour connaitre la consommation finale. */
	m_batterieRobiot.addBatterie(puissanceNecessaire);


	/* Mise � jour des coordonn�es du point courant une fois arriv�. */
	m_compasRobiot.setCompas(pointDestination);

	/* Extinction du moteur. */
	m_moteurRobiot.setMoteur(false);

} /* Cheminer */

/**************************************************************
*
* METHODE : CRobiot::Cheminer(coordonnees pointDestination)
* PRESENTATION : D�placement du Robiot. Cheminement entre sa position courant et la position du prochain arbre.
*
* ENTREE : 
* 	coordonnees pointDestination : coordonn�es du prochain arbre.
* 
***************************************************************/

void CRobiot::Cheminer(coordonnees pointDestination)
{
	coordonnees pointCourant = m_compasRobiot.getCompas();

	/* Calclul de la disance (Dijkstra). */
	int distance = algoDisjkra(m_compasRobiot.getCompas(), pointDestination);

	/* INFO CLIENT :
	 * 1 sur carte = 10 m en r�el. */
	distance = distance * 10;

	/* Allumage du moteur. */
	m_moteurRobiot.setMoteur(true);

	/* Consommation de la batterie :
	 * Carte m�re ARM : 12.5 Watts.
	 * Vitesse : 0.42 m.
	 * Moteur d'une roue : 14,0 Watts. */

	/* Calcul de la puissance en Joule. */
	int puissanceNecessaire = ((14 * 2) + 12.5) * (distance / 0.42); //J

	/* Incr�mentation de la batterie pour connaitre la consommation finale. */
	m_batterieRobiot.addBatterie(puissanceNecessaire);

	/* Mise � jour des coordonn�es du point courant une fois arriv�. */
	m_compasRobiot.setCompas(pointDestination);

	/* Extinction du moteur. */
	m_moteurRobiot.setMoteur(false);

} /* Cheminer */

/**************************************************************
*
* METHODE : CRobiot::Disjkra(coordonnees pointEntree, coordonnees pointSortie)
* PRESENTATION : Calcul de la distance avec l'algorithme de Disjkra.
*
* SORTIE : 
* 	int : distance la plus courte calcul�e par l'algotithme de Disjkra.
* 
***************************************************************/

int CRobiot::Disjkra(coordonnees pointEntree, coordonnees pointSortie)
{
	int distance = sqrt(pow((pointSortie.y - pointEntree.y), 2) - pow((pointSortie.x - pointEntree.x), 2));
	return (distance);

} /* Disjkra */

/**************************************************************
*
* METHODE : CRobiot::Mesurer()
* PRESENTATION : Mesure de l'arbre courant.
*
***************************************************************/

void CRobiot::Mesurer()
{
	m_mesureRobiot.setMesure(true);

	/* Consommation de la batterie :
	 * Carte m�re ARM : 12.5 Watts.
	 * Syst�me de mesure : 30,0 Watts.
	 * Dur�e de mesure : 5 mins. */

	/* Calcul de la puissance en Joule. */
	int puissanceNecessaire = (30 + 12.5) * 5 * 60;

	/* Incr�mentation de la batterie pour connaitre la consommation finale. */
	m_batterieRobiot.addBatterie(puissanceNecessaire);

	m_mesureRobiot.setMesure(false);

} /* Mesurer */

/**************************************************************
*
* METHODE : CRobiot::NombreArbre()
* PRESENTATION : Retourne le nombre d'arbre que le Robiot a � mesurer sur la cartographie.
*
* SORTIE : 
* 	int : nombre d'arbres.
* 
***************************************************************/

int CRobiot::NombreArbre()
{
	return (m_commandeRobiot.NombreArbre());

} /* NombreArbre */

/**************************************************************
*
* METHODE : CRobiot::BatterieUtilisee()
* PRESENTATION : Retourne la batterie consomm�e par le Robiot pour mesurer l'ensemble des arbres.
*
* SORTIE : 
* 	int : batterie en Joules.
* 
***************************************************************/

int CRobiot::BatterieUtilisee()
{
	return (m_batterieRobiot.getBatterie());

} /* BatterieUtilisee */

/**************************************************************
*
* METHODE : CRobiot::LargeurTerrain()
* PRESENTATION : Retourne la largeur du terrain en m�tre.
*
* SORTIE : 
* 	int : largeur du terrain en m�tre.
* 
***************************************************************/

int CRobiot::LargeurTerrain()
{
	return (m_capteurRobiot.getLargeurTerrain());

} /* LargeurTerrain */

/**************************************************************
*
* METHODE : CRobiot::LongueurTerrain()
* PRESENTATION : Retourne la longueur du terrain en m�tre.
*
* SORTIE : 
* 	int : longueur du terrain en m�tre.
* 
***************************************************************/

int CRobiot::LongueurTerrain()
{
	return (m_capteurRobiot.getLongueurTerrain());

} /* LongueurTerrain */

