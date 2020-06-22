/**************************************************************
*
* Reproduction et diffusion interdites.
* Developpé par INSA Rennes - 5 CDTI : COUTURAS / BODIN 
* Projet ROBIOT
*
* SOURCE : test.cpp
* PRESENTATION : Fichier de tests unitaires.
*
* AUTEUR : BODIN / COUTURAS
* VERSION CVS : V1
* DATE : 22/06/20
*
***************************************************************/

#include "pch.h"
#include "CCommande.h"
#include "CCapteur.h"
#include "CRobiot.h"
#include "CCompas.h"


<<<<<<< HEAD
TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

/*=============================
======= Tests Unitaires =======
=============================*/

/*==== Tests de la classe CCommande ====*/

/* Test de la fonction LireTableau() */

=======
/*Tests de la fonction LireTableau*/
>>>>>>> 6cdc3880fb7375e214f9397916cae15859cf999d
TEST(LireGrandTableau, LireTableau) {
	CCommande commande = CCommande();
	int res = commande.LireTableau("LISTE DE CONTROLE-Test_grand.txt");
	EXPECT_EQ(res, 0);
}

TEST(LireTableauVide, LireTableau) {
	CCommande commande = CCommande();
	int res = commande.LireTableau("LISTE DE CONTROLE-Test_vide.txt");
	EXPECT_EQ(res, 0);
}

TEST(LireTableauInexistant, LireTableau) {
	CCommande commande = CCommande();
	int res = commande.LireTableau("");
	EXPECT_EQ(res, 1);
}

/*==== Tests de la classe CCapteur ====*/

/* Test de la fonction LireCartographie() */

TEST(LireGrandTerrain, LireCartographie) {
	CCapteur capteur = CCapteur();
	int res = capteur.LireCartographie("CARTOGRPAHIE-Test_grand.txt");
	EXPECT_EQ(res, 0);
}

TEST(LireTerrainVide, LireCartographie) {
	CCapteur capteur = CCapteur();
	int res = capteur.LireCartographie("CARTOGRPAHIE-Test_vide.txt");
	EXPECT_EQ(res, 0);
}

TEST(LireTerrainInexistant, LireCartographie) {
	CCapteur capteur = CCapteur();
	int res = capteur.LireCartographie("");
	EXPECT_EQ(res, 1);
}

<<<<<<< HEAD

/*==== Tests de la classe CRobiot ====*/

/* Test de la fonction Cheminer(coordonnees pointDestination) */
=======
>>>>>>> 6cdc3880fb7375e214f9397916cae15859cf999d

/*Test de fonction Cheminer */
TEST(CheminerDistanceNulle, Cheminer) {
	CRobiot robiot = CRobiot();
	coordonnees point = { 1,5 };
	robiot.setPosition(point);
<<<<<<< HEAD
	robiot.Cheminer(point);
	coordonnees pointDepart =  robiot.getPosition();
	EXPECT_EQ(pointDepart.x, point.x);
	EXPECT_EQ(pointDepart.y, point.y);
	//EXPECT_EQ(res, 1);
}

/* Test de la fonction Cheminer(int indexArbreSuivant) */

/* Test de la fonction Disjkra(coordonnees pointEntree, coordonnees pointSortie) */

/* Test de la fonction NombreArbre() */

/* Test de la fonction BatterieUtilisee() */

/* Test de la fonction LargeurTerrain() */

/* Test de la fonction LongueurTerrain() */

;

=======
	robiot.Cheminer( point);
	coordonnees positionFinale =  robiot.getPosition();
	EXPECT_EQ(positionFinale.x, point.x);
	EXPECT_EQ(positionFinale.y, point.y);
}

TEST(CheminerDistanceNonNulle, Cheminer) {
	CRobiot robiot = CRobiot();
	coordonnees point = { 1,5 };
	robiot.Cheminer(point);
	coordonnees positionFinale =  robiot.getPosition();
	EXPECT_EQ(positionFinale.x, point.x);
	EXPECT_EQ(positionFinale.y, point.y);
}

TEST(CheminerDistanceGrande, Cheminer) {
	CRobiot robiot = CRobiot();
	coordonnees point = { 100,50 };
	robiot.Cheminer(point);
	coordonnees positionFinale =  robiot.getPosition();
	EXPECT_EQ(positionFinale.x, point.x);
	EXPECT_EQ(positionFinale.y, point.y);
}

TEST(Mesurer, Mesurer) {
	CRobiot robiot = CRobiot();
	coordonnees point = { 100,50 };
	robiot.Cheminer(point);
	coordonnees positionFinale = robiot.getPosition();
	EXPECT_EQ(positionFinale.x, point.x);
	EXPECT_EQ(positionFinale.y, point.y);
}
>>>>>>> 6cdc3880fb7375e214f9397916cae15859cf999d
