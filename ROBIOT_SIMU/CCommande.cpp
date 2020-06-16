#include "CCommande.h"


coordonnees getCoordonnees(int iNumero){

	if(iNumero < tab_coordonnees.size) {
		return tab_coordonnees[iNumero];
	}
}

void lireTableau(){
	
	FILE *pFile;
	pFile = fopen("LISTE DE CONTROLE", "r");
	if (pFile == NULL) {
	cout << "Probleme ouverture du fichier." << endl;
	}
	else {
		do{
			for(int i = 0, i < tab_coordonnees.size, i++){
				pFile >> tab_coordonnees[i].x;
				pFile >> tab_coordonnees[i].y;
			}
		}while(pFile != EOF);

		fclose(pFile);
	}

}
