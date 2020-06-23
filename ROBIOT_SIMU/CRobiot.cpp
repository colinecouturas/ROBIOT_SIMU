/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpe par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
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
#include <cmath>

/**************************************************************
*
* METHODE : main()
* PRESENTATION : Fonction principale.
*                Cr�ation d'un Robiot qui parcours une carte 
*                sur laquelle se trouvent des arbres et des 
*                obstacles. Le Robiot doit mesurer certains des 
*                arbres, et informer quant � la batterie qu'il 
*                a consomm� pour se faire.
*
* SORTIE :
* 	int : retourne 0 en cas de succ�s.
* 
***************************************************************/
/*
int main()
{
	/* Le robot ouvre la liste des coordonn�es. *
	/* Utilisation de l'algorithme de djiktra sur le tableau pour trouver le chemin le plus court. *

	int i = 0;

	/* D�finition d'un Robiot. *
	CRobiot petitRobiot = CRobiot();

	/* D�finition du point de d�part, auquel on va revenir � la fin. *
	coordonnees pointInitial = { 0, 0 };
	cout << "Le petit Robiot doit prendre des mesures sur un terrain de taille " << petitRobiot.getRobiotCapteur().getLargeurTerrain() << "m par " << petitRobiot.getRobiotCapteur().getLongueurTerrain() << "m."<< endl;
	cout << "Initialement le petit Robiot est positionne aux coordonnees {0,0}." << endl;

	for (i = 0; i < petitRobiot.getRobiotCommande().NombreArbre(); i++) {
		cout << "Il se dirige vers l'arbre numero " << i+1 << ". ";
		petitRobiot.Cheminer(i);
		cout << "Il mesure l'arbre " << i+1 <<". L'operation dure 5 mins." << endl;
		petitRobiot.Mesurer();
	}

	/* On revient au point de depart. *
	cout << "Le Robiot retourne a sa position initiale. ";
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
*                Dans ce constructeur on associe tous les 
*                param�tres connus avec un Robiot. En
*                particulier, on va lire les fichiers d'entr�e.
*                Le Robiot connait donc la position des obstacles, 
*                et des arbres � aller mesurer.
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
* PRESENTATION : D�placement du Robiot.  Cheminement entre sa 
*                position courante et la position du prochain 
*                arbre, et incr�mentation de la batterie en
*                fonction de la consommation de l'outil de 
*                mesure.
*
* ENTREE :
* 	int indexArbreSuivant : indice des coordonn�es du prochain arbre.
*
***************************************************************/

int CRobiot::Cheminer(int indexArbreSuivant)
{
	coordonnees pointCourant = m_compasRobiot.getCompas();
	coordonnees pointDestination = m_commandeRobiot.getCoordonnees(indexArbreSuivant);

	if (pointDestination.x > m_capteurRobiot.getLargeurTerrain() || pointDestination.y > m_capteurRobiot.getLongueurTerrain()) {
		cout << "Les coordonn�es de  l'arbre sont hors-terrain." << endl;
		return 1;
	}
	else {
		
		/* Calclul de la disance (Dijkstra). */
		float distance = Disjkra(m_compasRobiot.getCompas(), pointDestination);

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
		float puissanceNecessaire = ((14 * 4) + 12.5) * (distance / 0.42); //J

		/* Incr�mentation de la batterie pour connaitre la consommation finale. */
		m_batterieRobiot.addBatterie(puissanceNecessaire);


		/* Mise � jour des coordonn�es du point courant une fois arriv�. */
		m_compasRobiot.setCompas(m_commandeRobiot.getCoordonnees(indexArbreSuivant));

		/* Extinction du moteur. */
		m_moteurRobiot.setMoteur(false);

		cout << "La distance parcourue est de " << distance << "m." << endl;
		return 0;
	}
} /* Cheminer */

/**************************************************************
*
* METHODE : CRobiot::Cheminer(coordonnees pointDestination)
* PRESENTATION : Deplacement du Robiot. Cheminement entre sa 
*                position courante et la position du prochain 
*                arbre, et incr�mentation de la batterie en
*                fonction de la consommation de l'outil de 
*                mesure.
*
* ENTREE :
* 	coordonnees pointDestination : coordonn�es du prochain arbre.
*
***************************************************************/

int CRobiot::Cheminer(coordonnees pointDestination)
{
	if (pointDestination.x > m_capteurRobiot.getLargeurTerrain() || pointDestination.y > m_capteurRobiot.getLongueurTerrain()) {
		cout << "Les coordonn�es de  l'arbre sont hors-terrain" << endl;
		return 1;
	}
	else {
		coordonnees pointCourant = m_compasRobiot.getCompas();

		/* Calclul de la disance (Dijkstra). */
		float distance = Disjkra(m_compasRobiot.getCompas(), pointDestination);

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
		float puissanceNecessaire = ((14 * 4) + 12.5) * (distance / 0.42); //J

		/* Incr�mentation de la batterie pour connaitre la consommation finale. */
		m_batterieRobiot.addBatterie(puissanceNecessaire);

		/* Mise � jour des coordonn�es du point courant une fois arriv�. */
		m_compasRobiot.setCompas(pointDestination);

		/* Extinction du moteur. */
		m_moteurRobiot.setMoteur(false);

		cout << "La distance parcourue est de " << distance << "m." << endl;
		return 0;
	}
	

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

float CRobiot::Disjkra(coordonnees pointEntree, coordonnees pointSortie)
{	
	int calcul = abs((pointSortie.y - pointEntree.y) * (pointSortie.y - pointEntree.y) - (pointSortie.x - pointEntree.x) * (pointSortie.x - pointEntree.x));
	float distance = std::sqrt(calcul);
	return (distance);

} /* Disjkra */

/**************************************************************
*
* METHODE : CRobiot::Mesurer()
* PRESENTATION : Mesure de l'arbre courant et incr�mentation de 
*                la batterie en fonction de la consommation de 
*                l'outil de mesure.
*
***************************************************************/

void CRobiot::Mesurer()
{
	m_mesureRobiot.setMesure(true);

	/* Consommation de la batterie :
	 * Carte mere ARM : 12.5 Watts.
	 * Systeme de mesure : 30,0 Watts.
	 * Duree de mesure : 5 mins. */

	/* Calcul de la puissance en Joule. */
	float puissanceNecessaire = (30 + 12.5) * 5 * 60;

	/* Incrementation de la batterie pour connaitre la consommation finale. */
	m_batterieRobiot.addBatterie(puissanceNecessaire);

	m_mesureRobiot.setMesure(false);

} /* Mesurer */


void CRobiot::setPosition(coordonnees point) {
	m_compasRobiot.setCompas(point);
}

/**************************************************************
*
* METHODE : CRobiot::getRobiotCapteur()
* PRESENTATION : Fonction d'acc�s de l'attribut capteur du Robiot.
*                Permet d'acc�der au tableau des obstacles et des arbres 
*                correspondant au fichier CARTOGRAPHIE, et � la largeur 
*                et longueur du terrain.
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
* PRESENTATION : Fonction d'acc�s de l'attribut compas du Robiot.
*                Permet de connaitre la position du Robiot.
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
* PRESENTATION : Fonction d'acc�s de l'attribut batterie du Robiot.
*                Permet de connaitre le niveau de batterue du 
*                Robiot (en Joules).
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
* PRESENTATION : Fonction d'acc�s de l'attribut mesure du Robiot.
*                Permet de connaitre l'�tat du syst�me de mesure du Robiot.
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
* PRESENTATION : Fonction d'acc�s de l'attribut moteur du Robiot.
*                Permet de connaitre l'�tat du moteur du Robiot
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
* PRESENTATION : Fonction d'acc�s de l'attribut commande du Robiot.
*                Permet d'acc�der au tableau des coordonn�es du 
*                fichier LISTE DE CONTROLE, et au nombre d'arbres
*                du terrain � mesurer.  
*
* SORTIE :
* 	CCommande : commande du Robiot.
*
***************************************************************/

CCommande CRobiot::getRobiotCommande()
{
	return m_commandeRobiot;

} /* getRobiotCommande */

