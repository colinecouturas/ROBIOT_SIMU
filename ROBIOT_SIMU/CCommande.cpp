#include "CCommande.h"

coordonnees CCommande::getCoordonnees(int iNumero)
{
	if (iNumero < tabCoordonnees.size()) {
		return tabCoordonnees[iNumero];
	}
}

void CCommande::lireTableau(){
	
	ifstream file;
	file.open("LISTE DE CONTROLE");
	if (file) {
			do{
				for (int i = 0; i < tabCoordonnees.size(); i++) {
					coordonnees point;
					file >> point.x;
					file >> point.y;
					tabCoordonnees.push_back(point);
				}
		}while(!file.eof());
	}
	else {
		cout << "Probleme ouverture du fichier." << endl;
	}
	file.close();

}


