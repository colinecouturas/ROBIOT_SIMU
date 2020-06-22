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

#include "pch.h"
#include "CRobiot.h"
#include <math.h>

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

	for (i = 0; i < petitRobiot.getRobiotCommande().NombreArbre(); i++) {
		cout << "On se dirige vers l'arbre numero " << i+1 <<  endl;
		petitRobiot.Cheminer(i);
		cout << "On mesure l'arbre " << i+1  << endl;
		petitRobiot.Mesurer();
	}

	/* On revient au point de depart. */
	petitRobiot.Cheminer(pointInitial);

	cout << "C'est fini ! " << endl;
	cout << "Le petit Robiot a utilise " << petitRobiot.getRobiotBatterie().getBatterie() << " J pour mesurer les arbres de ce terrain." << endl;
	int tailleTerrain = petitRobiot.getRobiotCapteur().getLargeurTerrain() * petitRobiot.getRobiotCapteur().getLongueurTerrain();
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
	m_commandeRobiot.LireTableau("LISTE DE CONTROLE.txt");
	m_capteurRobiot.LireCartographie("CARTOGRAPHIE.txt");
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
	int distance = Disjkra(m_compasRobiot.getCompas(), m_commandeRobiot.getCoordonnees(indexArbreSuivant));

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
	int puissanceNecessaire = ((14 * 4) + 12.5) * (distance / 0.42); //J

	/* Incrémentation de la batterie pour connaitre la consommation finale. */
	m_batterieRobiot.addBatterie(puissanceNecessaire);


	/* Mise à jour des coordonnées du point courant une fois arrivé. */
	m_compasRobiot.setCompas(m_commandeRobiot.getCoordonnees(indexArbreSuivant));

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
	int distance = Disjkra(m_compasRobiot.getCompas(), pointDestination);

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
	int puissanceNecessaire = ((14 * 4) + 12.5) * (distance / 0.42); //J

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
	//int distance = sqrt(pow((pointSortie.y - pointEntree.y), 2) - pow((pointSortie.x - pointEntree.x), 2));
	int distance = sqrt(pow((pointSortie.y - pointEntree.y), 2) - pow((pointSortie.x - pointEntree.x), 2));
	// Boucle sur x et sur y 
	/*for (int i = 0; i < (pointSortie.x - pointEntree.x); i++){
		for (int j = 0; j < (pointSortie.y - pointEntree.y); j++) {

		}
		if (/*m_commande.isObstacle(point(x,y))/) {
			ne pas passer par cette case et arreter ce for?
		}
	}*/
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
* METHODE : CRobiot::getRobiotCapteur()
* PRESENTATION : Fonction getteur du capteur du Robiot.
*
* SORTIE :
* 	CCapteur : capteur du Robiot.
*
***************************************************************/

CCapteur CRobiot::getRobiotCapteur()
{
	return m_capteurRobiot;

} /* getRobiotCapteur */

/**************************************************************
*
* METHODE : CRobiot::getRobiotCompas()
* PRESENTATION : Fonction getteur de la position du Robiot.
*
* SORTIE :
* 	CCompas : position du Robiot.
*
***************************************************************/

CCompas CRobiot::getRobiotCompas()
{
	return m_compasRobiot;

} /* getRobiotCompas */

/**************************************************************
*
* METHODE : CRobiot::getRobiotBatterie()
* PRESENTATION : Fonction getteur de la batterie du Robiot.
*
* SORTIE :
* 	CBatterie : batterie du Robiot.
*
***************************************************************/

CBatterie CRobiot::getRobiotBatterie()
{
	return m_batterieRobiot;

} /* getRobiotBatterie */

/**************************************************************
*
* METHODE : CRobiot::getRobiotMesure()
* PRESENTATION : Fonction getteur de l'attribue mesure du Robiot.
*
* SORTIE :
* 	CMesure : attribut mesure du Robiot.
*
***************************************************************/

CMesure CRobiot::getRobiotMesure()
{
	return m_mesureRobiot;

} /* getRobiotMesure */

/**************************************************************
*
* METHODE : CRobiot::getRobiotMoteur()
* PRESENTATION : Fonction getteur du moteur du Robiot.
*
* SORTIE :
* 	CMoteur : moteur du Robiot.
*
***************************************************************/

CMoteur CRobiot::getRobiotMoteur()
{
	return m_moteurRobiot;

} /* getRobiotMoteur */

/**************************************************************
*
* METHODE : CRobiot::getRobiotCommande()
* PRESENTATION : Fonction getteur de la commande du Robiot.
*
* SORTIE :
* 	CCommande : commande du Robiot.
*
***************************************************************/

CCommande CRobiot::getRobiotCommande()
{
	return m_commandeRobiot;

} /* getRobiotCommande */
