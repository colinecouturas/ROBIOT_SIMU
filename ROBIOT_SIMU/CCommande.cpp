#include "CCommande.h"

coordonnees CCommande::getCoordonnees(int iNumero)
{
	if (iNumero < tab_coordonnees.size()) {
		return tab_coordonnees[iNumero];
	}
}

void CCommande::lireTableau(){
	
	ifstream file;
	file.open("LISTE DE CONTROLE");
	if (file) {
			do{
				for (int i = 0; i < tab_coordonnees.size(); i++) {
					coordonnees point;
					file >> point.x;
					file >> point.y;
					tab_coordonnees.push_back(point);
				}
		}while(!file.eof());
	}
	else {
		cout << "Probleme ouverture du fichier." << endl;
	}
	file.close();

}


