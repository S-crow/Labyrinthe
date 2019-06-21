#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include"fonctions.h"

//FONCTIONS FICHIER LABYRINTHE
void LIRE_FICHIER(MAZE* monlaby){
	FILE* fichier;
	int i,j;
	fichier=fopen("fichier.txt","r");

	if(fichier != NULL){
		fscanf(fichier, "%d %d %d %d %d %d", &(monlaby->nblignes), &(monlaby->nbcolonnes),
				&(monlaby->xEntree), &(monlaby->yEntree),
				&(monlaby->xSortie), &(monlaby->ySortie));

		monlaby->mat=ALLOC_MAT(monlaby->nblignes, monlaby->nbcolonnes);

		for(i=0;i<monlaby->nblignes;i++){
			for(j=0;j<monlaby->nbcolonnes;j++){

				fscanf(fichier, "%d", &(monlaby->mat[i][j]));

			}

		}
	}	

	fclose(fichier);
}


void AFFICHERLAB(MAZE* monlaby){    //On affiche le labyrinthe à partir du fichier

	int h,l;
	for(l=0;l<monlaby->nbcolonnes;l++) { printf("+--") ;} printf("+\n") ;

	for(h=0;h<monlaby->nblignes;h++) {
		printf("|") ;
		for(l=0;l<monlaby->nbcolonnes;l++) {

			if(l==(monlaby->nbcolonnes-1)){printf("  |");}

			else if (((((monlaby->mat[h][l])>>2)& 1)==1) && l<(monlaby->nbcolonnes)-1)  //Si mur à droite
				printf("  |") ;

			else
				printf("   ") ;
		}

		printf("\n") ;

		printf("+") ;
		for(l=0;l<monlaby->nbcolonnes;l++) {

			if ((((monlaby->mat[h][l])>>1)==1) && h<(monlaby->nblignes)-1) //Si mur en bas
				printf("--+") ;
			else if (h==(monlaby->nblignes)-1){printf("--+");}
			else
				printf("  +") ;
		}
		printf("\n") ;


	}
	printf("\n");


}	







//FONCTIONS MATRICE 

int** ALLOC_MAT(int nblignes, int nbcolonnes){
	int i;
	int** mat=malloc(nblignes*sizeof(int*));

	for(i=0;i<nblignes;i++){
		mat[i]=malloc(nbcolonnes*sizeof(int));
	}	
	return mat;
}


void INIT_MAT(int** mat, int nblignes, int nbcolonnes){
	int i,j;
	for(i=0;i<nblignes;i++){
		for(j=0;j<nbcolonnes;j++){
			mat[i][j]=15;  //On initialise la matrice pour qu'il y ait des murs partout
		}	

	}	
}	


void AFFICHE_MAT(int** mat, int nblignes, int nbcolonnes){
	int i,j;
	for(i=0;i<nblignes;i++){
		for(j=0;j<nbcolonnes;j++){
			printf("%d",mat[i][j]);
		}	
		printf("\n");

	}
}




void CONVERT_MAT_TO_LAB(int** mat, int nblignes, int nbcolonnes, MAZE* monlaby){  //On affiche le labyrinthe à partir de la matrice
	int i,j;

	for(j=0;j<nbcolonnes;j++) { printf("+--") ;} printf("+\n") ;

	for(i=0;i<nblignes;i++){
		printf("|");
		for(j=0;j<nbcolonnes;j++){
			if(j==nbcolonnes-1){printf("  |");}

			else if ((((mat[i][j]>>2)& 1)==1) && j<nbcolonnes-1)  //Si mur à droite
				printf("  |") ;

			else
				printf("   ");
		}
		printf("\n");
		printf("+");

		for(j=0;j<nbcolonnes;j++) {
			if ((((mat[i][j]>>1)& 1)==1) && i<nblignes-1) //Si mur en bas
				printf("--+") ;
			else if (i==nblignes-1){printf("--+");}

			else
				printf("  +") ;

		}
		printf("\n") ;
	}

	monlaby->mat=mat;
	monlaby->nblignes=nblignes;
	monlaby->nbcolonnes=nbcolonnes;

}	

void PLACER_ENTREE_SORTIE(MAZE* monlaby){   //On place l'entrée et la sortie en dur 

	switch(monlaby->nblignes){

		case 5:

			printf("\033[%d;%dH%s", 23, 5, "E");
			printf("\033[%d;%dH%s", 23+2*(monlaby->nblignes-3), 5+3*(monlaby->nbcolonnes-3)+1, "S");
			monlaby->i_positioncurseur=23;
			break;
		case 10:
			printf("\033[%d;%dH%s", 23, 5, "E");
			//system("picture-tube pacman.png");
			printf("\033[%d;%dH%s", 23+2*(monlaby->nblignes-3), 5+3*(monlaby->nbcolonnes-3)+1, "S");
			monlaby->i_positioncurseur=23;
			break;
		case 15:
			printf("\033[%d;%dH%s", 22, 5, "E");
			printf("\033[%d;%dH%s", 22+2*(monlaby->nblignes-3), 5+3*(monlaby->nbcolonnes-3)+1, "S");
			monlaby->i_positioncurseur=22;
			break;
		case 20:
			printf("\033[%d;%dH%s", 12, 5, "E");
			printf("\033[%d;%dH%s", 12+2*(monlaby->nblignes-3), 5+3*(monlaby->nbcolonnes-3)+1, "S");
			monlaby->i_positioncurseur=12;
			break;
		case 25:
			printf("\033[%d;%dH%s", 2, 5, "E");
			printf("\033[%d;%dH%s", 2+2*(monlaby->nblignes-3), 5+3*(monlaby->nbcolonnes-3)+1, "S");
			monlaby->i_positioncurseur=2;
			break;

		default:
			break;
	}



	monlaby->j_positioncurseur=5;


}


void PLACER_ENTREE_SORTIE_FICHIER(MAZE* monlaby){   //On place l'entrée et la sortie avec une equations


	printf("\033[%d;%dH%s", 2*monlaby->xEntree+2, 3*monlaby->yEntree+2 , "E");
	printf("\033[%d;%dH%s", 2*monlaby->xSortie+2, 3*monlaby->ySortie+2 , "S");

	monlaby->i_positioncurseur=2*monlaby->xEntree+2;
	monlaby->j_positioncurseur= 3*monlaby->yEntree+2;

}



void GENERATE_LAB(int** mat, int nblignes, int nbcolonnes){
	int a,b,alea;

	a=rand()%(nblignes-2)+1;   //On choisit une case aléatoirement
	b=rand()%(nbcolonnes-2)+1;

	alea=rand()%5+1; 

	switch(alea){

		case 2:
			mat[a-1][b]&=0xD;    //on supprime le mur dans la case voisine (du dessus) 
			mat[a][b]&=0x7;      //et dans la case courante (en haut -> coherence)
			break;
		case 3:
			mat[a+1][b]&=0x7;
			mat[a][b]&=0xD;//mettre le 2e bit à 0

			break;
		case 4:
			mat[a][b-1]&=0xB;
			mat[a][b]&=0xE; //mettre le 1er bit à 0
			break;
		case 5:
			mat[a][b+1]&=0xE;
			mat[a][b]&=0xB;//mettre le 3e bit à 0
			break;
		default:
			break;
	}

}




//FONCTIONS PILE (utilisée pour l'algorithme Backtrack)

void empiler(Pile *pile, int nvAbscisse, int nvOrdonnee)
{
	Element *nouveau = malloc(sizeof(*nouveau));
	if (pile == NULL)
	{
		exit(EXIT_FAILURE);
	}

	nouveau->abscisse = nvAbscisse;
	nouveau->ordonnee = nvOrdonnee;
	nouveau->suivant = pile->premier;
	pile->premier = nouveau;
}


Element* depiler(Pile *pile)
{
	if (pile == NULL)
	{
		exit(EXIT_FAILURE);
	}

	int abscisseDepile = 0;
	int ordonneeDepile = 0;

	Element *elementDepile = pile->premier;

	if (pile != NULL && pile->premier != NULL)
	{
		abscisseDepile = elementDepile->abscisse;
		ordonneeDepile = elementDepile->ordonnee;
		pile->premier = elementDepile->suivant;
		free(elementDepile);
	}
	return elementDepile;

}

void afficherPile(Pile *pile)
{
	if (pile == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Element *actuel = pile->premier;

	while (actuel != NULL)
	{
		printf("%d %d\n", actuel->abscisse, actuel->ordonnee);
		actuel = actuel->suivant;
	}

	printf("\n");
}


Pile *initialiser(int abscisse, int ordonnee)
{
	Pile *pile = malloc(sizeof(*pile));
	Element *element = malloc(sizeof(*element));

	if (pile == NULL || element == NULL)
	{
		exit(EXIT_FAILURE);
	}

	element->abscisse = abscisse;
	element->ordonnee = ordonnee;
	element->suivant = NULL;
	pile->premier = element;

	return pile;
}





void BACKTRACK2(MAZE* monlaby){

	int a,b,nbsauts;
	a=monlaby->xEntree;
	b=monlaby->yEntree;
	Pile *maPile = initialiser(a,b);
	//depiler(maPile);	
	int mur=1;

	do {

		switch(mur){

			case 1:

				if ((((monlaby->mat[a][b]>>2)& 1)==1)) {  //Si mur à droite 
					mur++;
				}
				else {
				
					//if(((monlaby->mat[a][b++]>>4)&1)==0){
					b++;	
					monlaby->j_positioncurseur+=3;
					printf("\033[%d;%dH%s", monlaby->i_positioncurseur, monlaby->j_positioncurseur, "*");
					empiler(maPile,a,b);
					monlaby->mat[a][b]=(monlaby->mat[a][b] | 0x10);  //Pour marquer la cellule comme visitée

						nbsauts++;



					//}
				}	
				break;
			case 2:
				if ((((monlaby->mat[a][b]>>1)& 1)==1)) {  //Si mur en bas
					mur++;	
				}
				else {

					//if(a<monlaby->nblignes-1){
					//if((((monlaby->mat[a++][b]>>1)&1)==0)){

					a++;
					empiler(maPile,a,b);
					monlaby->mat[a][b]=(monlaby->mat[a][b] | 0x10);  //Pour marquer la cellule comme visitée
					monlaby->i_positioncurseur+=2;
					printf("\033[%d;%dH%s", monlaby->i_positioncurseur, monlaby->j_positioncurseur, "*");
					mur--;

						nbsauts++;

				}

				break;
			case 3:
				if ((((monlaby->mat[a][b]>>3)& 1)==1)) {  //Si mur en haut
					mur++;	
				}
				else {

					//if(a>0){
					//if(((monlaby->mat[a--][b]>>4)&1)==0) {

					a--;
					empiler(maPile,a,b);
					monlaby->mat[a][b]=(monlaby->mat[a][b] | 0x10);  //Pour marquer la cellule comme visitée
					monlaby->i_positioncurseur-=2;
					printf("\033[%d;%dH%s", monlaby->i_positioncurseur, monlaby->j_positioncurseur, "*");
				
						nbsauts++;

					
					
					//}
					/*					
					else {

						depiler(maPile);
					
						a=maPile->premier->abscisse;
						b=maPile->premier->ordonnee;
					}

*/				//}
					//}
				}


				break;
			case 4:
				if ((((monlaby->mat[a][b]>>0)& 1)==1)) {  //Si mur à gauche
					mur=1;	
				}
				else {

					//if((((monlaby->mat[a][b--]>>4)&1)==0)){ //&& (((monlaby->mat[a][b]>>0)&1)==0)){
					b--;
					empiler(maPile,a,b);
					monlaby->mat[a][b]=(monlaby->mat[a][b] | 0x10);  //Pour marquer la cellule comme visitée
					monlaby->j_positioncurseur-=3;
					printf("\033[%d;%dH%s", monlaby->i_positioncurseur, monlaby->j_positioncurseur, "*");
					mur=2;

						nbsauts++;
				}

				break;
			default:

				while ((((monlaby->mat[a][b--]>>4)&1)==1)) {  
				depiler(maPile);

				a=maPile->premier->abscisse;
				b=maPile->premier->ordonnee;
				mur=4;
				}

				break;

				
		}
usleep(100000);
fflush(stdout);
srand(time(NULL));
if(nbsauts == 20){
	b--;
	monlaby->mat[a][b]=(monlaby->mat[a][b] | 0x10);  //Pour marquer la cellule comme visitée
	monlaby->j_positioncurseur-=3;
	printf("\033[%d;%dH%s", monlaby->i_positioncurseur, monlaby->j_positioncurseur, "*");
	mur=2;
	nbsauts=0;
}
	

//afficherPile(maPile);
	}  while (!(a==monlaby->xSortie && b==monlaby->ySortie));


	printf("\033[%d;%dH%s", 54, 0, "");
	printf("Bravo vous avez resolu le labyrinthe !");
//afficherPile(maPile);
}




//Premier test de backtrack (non abouti)
/*
void BACKTRACK(MAZE* monlaby){

	int a,b;
	a=monlaby->xEntree;
	b=monlaby->yEntree;

	Pile *maPile = initialiser(a,b);	
	do {
		//afficherPile(maPile);
		if ((((monlaby->mat[a][b]>>2)& 1)==1)) {  //Si mur à droite 
			if ((((monlaby->mat[a][b]>>1)& 1)==1) ) {  //Si mur en bas 	
				if ((((monlaby->mat[a][b]>>3)& 1)==1)) { //Si mur en haut 
					if (((monlaby->mat[a][b]& 1)==1)) { //Si mur à gauche
						printf("\033[%d;%dH%s", 54, 0, "");
						exit(-1);
					}
					else {
						if(((monlaby->mat[a][b]>>4)&1)==1){
							depiler(maPile);
							exit(-1);
							a=maPile->premier->abscisse;
							b=maPile->premier->ordonnee;
						}

						else {	

							(monlaby->mat[a][b]>>4)|1;  //Pour marquer la cellule comme visitée
							empiler(maPile,a,b);
							b--;
							monlaby->j_positioncurseur-=3;
							printf("\033[%d;%dH%s", monlaby->i_positioncurseur, monlaby->j_positioncurseur, "*");
						}
					}
				}
				else {	
					if(((monlaby->mat[a][b]>>4)&1)==1){
						depiler(maPile);
						a=maPile->premier->abscisse;
						b=maPile->premier->ordonnee;

					}
					else {
						(monlaby->mat[a][b]>>4)|1;
						empiler(maPile,a,b);
						a--;
						monlaby->i_positioncurseur-=2;
						printf("\033[%d;%dH%s", monlaby->i_positioncurseur, monlaby->j_positioncurseur, "*");
					}
				}	
			}
			else {
				if(((monlaby->mat[a][b]>>4)&1)==1){     
					depiler(maPile);
					a=maPile->premier->abscisse;
					b=maPile->premier->ordonnee;

				}
				else {
					(monlaby->mat[a][b]>>4)|1;
					empiler(maPile,a,b);
					a++;
					monlaby->i_positioncurseur+=2;
					printf("\033[%d;%dH%s", monlaby->i_positioncurseur, monlaby->j_positioncurseur, "*");
				}


			}
		}

		else {	
			if(((monlaby->mat[a][b]>>4)&1)==1){	
				depiler(maPile);
				a=maPile->premier->abscisse;
				b=maPile->premier->ordonnee;

			}
			else {
				(monlaby->mat[a][b]>>4)|1;
				empiler(maPile,a,b);
				b++;
				monlaby->j_positioncurseur+=3;
				printf("\033[%d;%dH%s", monlaby->i_positioncurseur, monlaby->j_positioncurseur, "*");
			}
		}
	} while (!(a==monlaby->xSortie && b==monlaby->ySortie));

	printf("\033[%d;%dH%s", 54, 0, "");

}

*/



