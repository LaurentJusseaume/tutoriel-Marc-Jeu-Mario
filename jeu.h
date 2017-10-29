#ifndef JEU_H_
#define JEU_H_

void jouer(SDL_Surface* ecran);
void deplacerJoueur(int carte[][NB_BLOC_HAUTEUR], SDL_Rect*pos, int direction);
void deplacerCaisse(int*premiereCase, int*secondeCase);
int chargerNiveau(int niveau[][NB_BLOC_HAUTEUR]);

SDL_Surface *mario[4]={NULL};
SDL_Surface *mur=NULL, *caisse=NULL, *caisseOK=NULL, *objectif=NULL, *marioActuel=NULL,*menu=NULL;
SDL_Surface* ecran=NULL;
SDL_Rect position, positionJoueur;
SDL_Event event;
int objectifRestant=3;
int carte2[NB_BLOC_LARGEUR][NB_BLOC_HAUTEUR]={0};

#endif
