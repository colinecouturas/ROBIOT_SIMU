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


/*=============================
======= Tests Unitaires =======
=============================*/

/*==== Tests de la classe CCommande ====*/

/* Test de la fonction LireTableau() */

TEST( LireTableau, LireGrandTableau) {
	CCommande commande = CCommande();
	int res = commande.LireTableau("LISTE DE CONTROLE-Test_grand.txt");
	EXPECT_EQ(res, 0);
}

TEST(LireTableau, LireTableauVide) {
	CCommande commande = CCommande();
	int res = commande.LireTableau("LISTE DE CONTROLE-Test_vide.txt");
	EXPECT_EQ(res, 0);
}

TEST(LireTableau, LireTableauInexistant) {
	CCommande commande = CCommande();
	int res = commande.LireTableau("");
	EXPECT_EQ(res, 1);
}

/*==== Tests de la classe CCapteur ====*/

/* Test de la fonction LireCartographie() */

TEST(LireCartographie, LireGrandTerrain ) {
	CCapteur capteur = CCapteur();
	int res = capteur.LireCartographie("CARTOGRPAHIE-Test_grand.txt");
	EXPECT_EQ(res, 0);
}

TEST(LireCartographie, LireTerrainVide) {
	CCapteur capteur = CCapteur();
	int res = capteur.LireCartographie("CARTOGRPAHIE-Test_vide.txt");
	EXPECT_EQ(res, 0);
}

TEST(LireCartographie, LireTerrainInexistant) {
	CCapteur capteur = CCapteur();
	int res = capteur.LireCartographie("");
	EXPECT_EQ(res, 1);
}


/*==== Tests de la classe CRobiot ====*/

/* Test initialisation classe CRobiot */
TEST(CRobiot, construction) {
	CRobiot robiot = CRobiot();	
	EXPECT_EQ(robiot.getRobiotBatterie().getBatterie(), 0);
	EXPECT_EQ(robiot.getRobiotMoteur().getMoteur(),false);
	EXPECT_EQ(robiot.getRobiotCapteur().getLargeurTerrain(), 50);
	EXPECT_EQ(robiot.getRobiotCapteur().getLongueurTerrain(), 12);
	EXPECT_EQ(robiot.getRobiotMesure().getMesure(), false);
	EXPECT_EQ(robiot.getRobiotCompas().getCompasX(), 0);
	EXPECT_EQ(robiot.getRobiotCompas().getCompasY(), 0);

}

/* Test de la fonction Cheminer(coordonnees pointDestination) */
TEST(Cheminer, CheminerDistanceNulle ) {
	CRobiot robiot = CRobiot();
	coordonnees point = { 1,5 };
	robiot.setPosition(point);
	int res = robiot.Cheminer(point);
	coordonnees pointDepart = robiot.getRobiotCompas().getCompas();
	EXPECT_EQ(pointDepart.x, point.x);
	EXPECT_EQ(pointDepart.y, point.y);
	EXPECT_EQ(res, 0);
}

TEST(Cheminer, CheminerDistanceNonNulle ) {
	CRobiot robiot = CRobiot();
	coordonnees point = { 1,5 };
	int res = robiot.Cheminer(point);
	coordonnees positionFinale = robiot.getRobiotCompas().getCompas();
	EXPECT_EQ(positionFinale.x, point.x);
	EXPECT_EQ(positionFinale.y, point.y);
	EXPECT_EQ(res, 0);
}

TEST(Cheminer, CheminerAbreHorsTerrain ) {
	CRobiot robiot = CRobiot();
	coordonnees point = { 100,50 };
	int res = robiot.Cheminer(point);
	EXPECT_EQ(res,1);
}


/* Test de la fonction Mesurer */
TEST(Mesurer, Mesurer) {
	CRobiot robiot = CRobiot();
	int puissance = (30 + 12.5) * 5 * 60;
	robiot.Mesurer();
	EXPECT_EQ(robiot.getRobiotBatterie().getBatterie(), puissance);
}
