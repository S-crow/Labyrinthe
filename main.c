#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	MAZE* monlaby;
	monlaby=malloc(sizeof(*monlaby));

	int choixMenu;
	int nblignes, nbcolonnes;	    
	int iteration;


	/*printf("
	  __  __     _     _____ _____      ____    ___   _  __     __ _____  ____    \
	  |  \/  |   / \   |__  /| ____|    / ___|  / _ \ | | \ \   / /| ____||  _ \   \
	  | |\/| |  / _ \    / / |  _|      \___ \ | | | || |  \ \ / / |  _|  | |_) |  \
	  | |  | | / ___ \  / /_ | |___      ___) || |_| || |___\ V /  | |___ |  _ <   \
	  |_|  |_|/_/   \_\/____||_____|    |____/  \___/ |_____|\_/   |_____||_| \_\ ");

	 */

	printf("\n\n========================\n");
	printf("====== LABYRINTHE ======\n");
	printf("========================\n\n");

	printf("1. Generer un labyrinthe aleatoire\n");
	printf("2. Charger un labyrinthe\n");
	printf("3. Quitter\n");


	do{

		scanf("%d", &choixMenu);

		switch (choixMenu)
		{
			case 1:
				printf("\nVous avez choisi de generer un labyrinthe\n\n");
				printf("Nombre de lignes ?\t"); scanf("%d", &nblignes);
				printf("Nombre de colonnes ?\t"); scanf("%d", &nbcolonnes);

				int** mat=ALLOC_MAT(nblignes,nbcolonnes);
				INIT_MAT(mat,nblignes,nbcolonnes);   //On initialise la matrice avec des murs partout
				printf("\n\n");

				for(iteration=0;iteration<nblignes*nbcolonnes*3;iteration++){
					GENERATE_LAB(mat,nblignes,nbcolonnes); //On casse des murs aléatoirement
				}


				//AFFICHE_MAT(mat,nblignes,nbcolonnes);

				//printf("\033[H\033[J");   //Clear l'ecran
				
				CONVERT_MAT_TO_LAB(mat,nblignes,nbcolonnes,monlaby); //On affiche le labyrinthe à partir de la matrice
				monlaby->xEntree=1;
				monlaby->yEntree=1;
				monlaby->xSortie=nblignes-2;
				monlaby->ySortie=nbcolonnes-2;
				
				
				PLACER_ENTREE_SORTIE(monlaby);

				BACKTRACK2(monlaby);
				break;
			case 2:
				printf("\n\n\nChargement du fichier de labyrinthe...\n\n\n\n");
				sleep(1);       
				LIRE_FICHIER(monlaby);


				//AFFICHERLAB(monlaby);   //On peut afficher le labyrinthe directement
				
					
				printf("\033[H\033[J");

				CONVERT_MAT_TO_LAB(monlaby->mat,monlaby->nblignes,monlaby->nbcolonnes,monlaby);  //ou à partir de sa matrice			
				PLACER_ENTREE_SORTIE_FICHIER(monlaby);

				BACKTRACK2(monlaby);
				break;
			case 3:
				printf("\nA bientot...\n\n");
				exit(-1);       
				break;
			default:
				printf("\nVeuillez choisir l'une des options");
				break;
		}

		printf("\n\n");

	} while (choixMenu!=1 && choixMenu!=2 && choixMenu!=3);

	printf("\033[%d;%dH%s", 54, 0, "");

	return 0;


}	
