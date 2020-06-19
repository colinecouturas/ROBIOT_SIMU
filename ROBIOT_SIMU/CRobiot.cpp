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

/**************************************************************
*
* METHODE : main()
* PRESENTATION : Fonction principale.
* Création d'un Robiot qui parcours une carte sur laquelle se trouvent des arbres et des obstacles.
* Le Robiot doit mesurer certains des arbres, et informer quant à la batterie qu'il a consommé pour se faire.
*
* SORTIE :
* 	int : retourne 0 en cas de succès.
* 
***************************************************************/

int main()
{
	/* Le robot ouvre la liste des coordonnées. */
	/* Utilisation de l'algorithme de djiktra sur le tableau pour trouver le chemin le plus court. */

	int i = 0;

	/* Définition d'un Robiot. */
	CRobiot petitRobiot = CRobiot();

	/* Définition du point de départ, auquel on va revenir à la fin. */
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
* Dans ce constructeur on associe tous les paramètres connus avec un Robiot.
* En particulier, on va lire les fichiers d'entrée.
* Le Robiot connait donc la position des obstacles, et des arbres à aller mesurer.
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

void CRobiot::Cheminer(int indexArbreSuivant)
{	
	coordonnees pointCourant = m_compasRobiot.getCompas();

	/* Calclul de la disance (Dijkstra). */
	int distance = algoDisjkra(m_compasRobiot.getCompas(), m_commandeRobiot.getCoordonnees(indexArbreSuivant));

	/* INFO CLIENT :
	 * 1 sur carte = 10 m en réel. */
	distance = distance * 10;

	/* Allumage du moteur. */
	m_moteurRobiot.setMoteur(true);

	/* Consommation de la batterie :
	 * Carte mère ARM : 12.5 Watts.
	 * Vitesse : 0.42 m.
	 * Moteur d'une roue : 14,0 Watts. */

	/* Calcul de la puissance en Joule. */
	int puissanceNecessaire = ((14 * 2) + 12.5) * (distance / 0.42); //J

	/* Incrémentation de la batterie pour connaitre la consommation finale. */
	m_batterieRobiot.addBatterie(puissanceNecessaire);


	/* Mise à jour des coordonnées du point courant une fois arrivé. */
	m_compasRobiot.setCompas(pointDestination);

	/* Extinction du moteur. */
	m_moteurRobiot.setMoteur(false);

} /* Cheminer */

/**************************************************************
*
* METHODE : CRobiot::Cheminer(coordonnees pointDestination)
* PRESENTATION : Déplacement du Robiot. Cheminement entre sa position courant et la position du prochain arbre.
*
* ENTREE : 
* 	coordonnees pointDestination : coordonnées du prochain arbre.
* 
***************************************************************/

void CRobiot::Cheminer(coordonnees pointDestination)
{
	coordonnees pointCourant = m_compasRobiot.getCompas();

	/* Calclul de la disance (Dijkstra). */
	int distance = algoDisjkra(m_compasRobiot.getCompas(), pointDestination);

	/* INFO CLIENT :
	 * 1 sur carte = 10 m en réel. */
	distance = distance * 10;

	/* Allumage du moteur. */
	m_moteurRobiot.setMoteur(true);

	/* Consommation de la batterie :
	 * Carte mère ARM : 12.5 Watts.
	 * Vitesse : 0.42 m.
	 * Moteur d'une roue : 14,0 Watts. */

	/* Calcul de la puissance en Joule. */
	int puissanceNecessaire = ((14 * 2) + 12.5) * (distance / 0.42); //J

	/* Incrémentation de la batterie pour connaitre la consommation finale. */
	m_batterieRobiot.addBatterie(puissanceNecessaire);

	/* Mise à jour des coordonnées du point courant une fois arrivé. */
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
* 	int : distance la plus courte calculée par l'algotithme de Disjkra.
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
	 * Carte mère ARM : 12.5 Watts.
	 * Système de mesure : 30,0 Watts.
	 * Durée de mesure : 5 mins. */

	/* Calcul de la puissance en Joule. */
	int puissanceNecessaire = (30 + 12.5) * 5 * 60;

	/* Incrémentation de la batterie pour connaitre la consommation finale. */
	m_batterieRobiot.addBatterie(puissanceNecessaire);

	m_mesureRobiot.setMesure(false);

} /* Mesurer */

/**************************************************************
*
* METHODE : CRobiot::NombreArbre()
* PRESENTATION : Retourne le nombre d'arbre que le Robiot a à mesurer sur la cartographie.
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
* PRESENTATION : Retourne la batterie consommée par le Robiot pour mesurer l'ensemble des arbres.
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
* PRESENTATION : Retourne la largeur du terrain en mètre.
*
* SORTIE : 
* 	int : largeur du terrain en mètre.
* 
***************************************************************/

int CRobiot::LargeurTerrain()
{
	return (m_capteurRobiot.getLargeurTerrain());

} /* LargeurTerrain */

/**************************************************************
*
* METHODE : CRobiot::LongueurTerrain()
* PRESENTATION : Retourne la longueur du terrain en mètre.
*
* SORTIE : 
* 	int : longueur du terrain en mètre.
* 
***************************************************************/

int CRobiot::LongueurTerrain()
{
	return (m_capteurRobiot.getLongueurTerrain());

} /* LongueurTerrain */

