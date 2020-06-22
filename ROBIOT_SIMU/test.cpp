#include "pch.h"
#include "CCommande.h"
#include "CCapteur.h"
#include "CRobiot.h"
#include "CCompas.h"


TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

/*Tests de la fonction LireTableau*/
TEST(LireGrandTableau, LireTableau) {
	CCommande commande = CCommande();
	int res = commande.LireTableau("");
	EXPECT_EQ(res, 0);
}

TEST(LireTableauInexistant, LireTableau) {
	CCommande commande = CCommande();
	int res = commande.LireTableau("");
	EXPECT_EQ(res, 1);
}

TEST(LireTableauVide, LireTableau) {
	CCommande commande = CCommande();
	int res = commande.LireTableau("");
	EXPECT_EQ(res, 0);
}

/*Tests de la fonction LireCartographie*/
TEST(LireGrandTerrain, LireCartographie) {
	CCapteur capteur = CCapteur();
	int res = capteur.LireCartographie("");
	EXPECT_EQ(res, 0);
}

TEST(LireTerrainVide, LireCartographie) {
	CCapteur capteur = CCapteur();
	int res = capteur.LireCartographie("");
	EXPECT_EQ(res, 0);
}

TEST(LireTerrainInexistant, LireCartographie) {
	CCapteur capteur = CCapteur();
	int res = capteur.LireCartographie("");
	EXPECT_EQ(res, 1);
}

/*Test de fonction Cheminer */

TEST(MesurerDistanceNulle, Cheminer) {
	CRobiot robiot = CRobiot();
	coordonnees point = { 1,5 };
	robiot.setPosition(point);
	robiot.Cheminer( point);
	coordonnees pointDepart =  robiot.getPosition();
	EXPECT_EQ(pointDepart.x, point.x);
	EXPECT_EQ(pointDepart.y, point.y);
	//EXPECT_EQ(res, 1);
}