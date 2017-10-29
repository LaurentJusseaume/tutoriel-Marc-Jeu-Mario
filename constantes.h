#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define TAILLE_BLOC            34
#define NB_BLOC_LARGEUR        12
#define NB_BLOC_HAUTEUR        12
#define LARGEUR_FENETRE        TAILLE_BLOC*NB_BLOC_LARGEUR
#define HAUTEUR_FENETRE        TAILLE_BLOC*NB_BLOC_HAUTEUR

   enum{
	   HAUT,
	   BAS,
	   GAUCHE,
	   DROITE
   };

   enum{
   	MUR,
   	MARIO,
   	CAISSE,
   	CAISSE_OK,
   	OBJECTIF,
   	VIDE
   };


#endif
