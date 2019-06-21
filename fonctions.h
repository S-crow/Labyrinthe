//Structure labyrinthe
typedef struct labyrinthe MAZE;
struct labyrinthe
{
	int nblignes;
	int nbcolonnes;
	int xEntree, xSortie;
	int yEntree, ySortie;
	int i_positioncurseur, j_positioncurseur;
	//int mat[10][10];
	int** mat;

};


//Fonctions gestion du labyrinthe
void LIRE_FICHIER(MAZE*);
void AFFICHERLAB(MAZE*);
void RESOLVE(MAZE*);
void BACKTRACK(MAZE*);

void BACKTRACK2(MAZE*);
void CONVERT_MAT_TO_LAB(int**,int,int,MAZE*);
void GENERATE_LAB(int**,int,int);
void PLACER_ENTREE_SORTIE(MAZE*);


//Fonctions gestion de matrice
int** ALLOC_MAT(int,int);
void INIT_MAT(int**,int,int);
void AFFICHE_MAT(int**,int,int);


//Gestion de pile
typedef struct Element Element;
struct Element
{
	//unsigned short cell;
	int abscisse;
	int ordonnee;
        Element *suivant;	
};	

typedef struct Pile Pile;
struct Pile
{
	Element *premier;
};


Pile *initialiser(int,int);
void afficherPile(Pile *pile);
void empiler(Pile *pile, int abscisse, int ordonnee);
Element* depiler(Pile *pile);

	
