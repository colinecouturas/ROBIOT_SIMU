#include "pch.h"
#include "CCommande.h"
#include "CCapteur.h"
#include "CRobiot.h"
#include "CCompas.h"


/*Tests de la fonction LireTableau*/
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

/*Tests de la fonction LireCartographie*/
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


/*Test de fonction Cheminer */
TEST(CheminerDistanceNulle, Cheminer) {
	CRobiot robiot = CRobiot();
	coordonnees point = { 1,5 };
	robiot.setPosition(point);
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
