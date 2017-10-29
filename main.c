#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "jeu.h"
#include "editeur.h"

/* Fonction qui redessine l'ecran */
static void redessiner(SDL_Surface* ecran){
	SDL_Rect position;

	SDL_Surface* murAncien[12][12];
	int i, j;

	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	for(i=0;i<NB_BLOC_LARGEUR;i++){
		for(j=0;j<NB_BLOC_HAUTEUR;j++){
			position.x=i*TAILLE_BLOC;
			position.y=j*TAILLE_BLOC;
			switch(carte2[i][j]){
			case MUR:
				murAncien[i][j]=IMG_Load("..\\mur.jpg");
				SDL_BlitSurface(murAncien[i][j], NULL, ecran, &position);
				break;
			case CAISSE:
				murAncien[i][j]=IMG_Load("..\\caisse.jpg");
				SDL_BlitSurface(murAncien[i][j], NULL, ecran, &position);
				break;
			case CAISSE_OK:
				murAncien[i][j]=IMG_Load("..\\caisse_ok.jpg");
				SDL_BlitSurface(murAncien[i][j], NULL, ecran, &position);
				break;
			case OBJECTIF:
				murAncien[i][j]=IMG_Load("..\\objectif.png");
				SDL_BlitSurface(murAncien[i][j], NULL, ecran, &position);
				break;

			}

		}
	}
	position.x=positionJoueur.x*TAILLE_BLOC;
	position.y=positionJoueur.y*TAILLE_BLOC;
	SDL_BlitSurface(marioActuel, NULL, ecran, &position);

	SDL_Flip(ecran);
}

static void pause(SDL_Surface* ecran)
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
            	switch(event.key.keysym.sym){
            	case SDLK_ESCAPE:
            		continuer=0;
            		break;
            	case SDLK_UP:
            		marioActuel=mario[HAUT];
            		deplacerJoueur(carte2, &positionJoueur, HAUT);
            		break;
            	case SDLK_DOWN:
            		printf("touche bas\n");
            		marioActuel=mario[BAS];
            		deplacerJoueur(carte2, &positionJoueur, BAS);
            		break;
            	case SDLK_RIGHT:
            		marioActuel=mario[DROITE];
            		deplacerJoueur(carte2, &positionJoueur, DROITE);
            		break;
            	case SDLK_LEFT:
            		marioActuel=mario[GAUCHE];
            		deplacerJoueur(carte2, &positionJoueur, GAUCHE);
            		break;
            	case SDLK_KP1:
            		jouer(ecran);
            		break;
            	case SDLK_KP2:
            		editeur(ecran);
            		break;
            	default:
            		break;
            	}
            	break;
        }
        /*if (!objectifRestant){
        	continuer=0;
        }*/
        if (objectifRestant != 0)
        	redessiner(ecran);
    }
}

void editeur(SDL_Surface* ecran){

}

void deplacerJoueur(int carte[][NB_BLOC_HAUTEUR], SDL_Rect*pos, int direction){
	switch (direction){
	case HAUT:
		if(pos->y-1<0)
			break;
		if(carte[pos->x][pos->y-1]==MUR)
			break;
		if((carte[pos->x][pos->y-1]==CAISSE)&&
				( (pos->y-2<0) ||(carte[pos->x][pos->y-2]==MUR) || (carte[pos->x][pos->y-2]==CAISSE)  ))
			break;
		if(carte[pos->x][pos->y-1]==CAISSE)
			deplacerCaisse(&carte2[pos->x][pos->y-1], &carte2[pos->x][pos->y-2]);
	    pos->y--;
	    break;
	case BAS:
		printf("position=%d, %d", pos->x, pos->y);
		if(pos->y+1>NB_BLOC_HAUTEUR)
			break;
		if(carte[pos->x][pos->y+1]==MUR)
			break;
		if((carte[pos->x][pos->y+1]==CAISSE)&&
				( (pos->y+2>NB_BLOC_HAUTEUR) ||(carte[pos->x][pos->y+2]==MUR) || (carte[pos->x][pos->y+2]==CAISSE)  ))
			break;
		if(carte[pos->x][pos->y+1]==CAISSE)
			deplacerCaisse(&carte2[pos->x][pos->y+1], &carte2[pos->x][pos->y+2]);
		pos->y++;
		break;
	case GAUCHE:
		if(pos->x-1<0)
			break;
		if(carte[pos->x-1][pos->y]==MUR)
			break;
		if((carte[pos->x-1][pos->y]==CAISSE)&&
				( (pos->x-2<0) ||(carte[pos->x-2][pos->y]==MUR) || (carte[pos->x-2][pos->y]==CAISSE)  ))
			break;
		if(carte[pos->x-1][pos->y]==CAISSE)
			deplacerCaisse(&carte2[pos->x-1][pos->y], &carte2[pos->x-2][pos->y]);
		pos->x--;
		break;
	case DROITE:
		if(pos->x+1>NB_BLOC_LARGEUR)
			break;
		if(carte[pos->x+1][pos->y]==MUR)
			break;

		if((carte[pos->x+1][pos->y]==CAISSE)&&
				( (pos->x+2>NB_BLOC_LARGEUR) ||(carte[pos->x+2][pos->y]==MUR) || (carte[pos->x+2][pos->y]==CAISSE)  ))
			break;
		if(carte[pos->x+1][pos->y]==CAISSE)
			deplacerCaisse(&carte2[pos->x+1][pos->y], &carte2[pos->x+2][pos->y]);

		pos->x++;
		break;
	}
}

void deplacerCaisse(int*premiereCase, int*secondeCase){
	if(*premiereCase==CAISSE || *premiereCase==CAISSE_OK){
		if(*secondeCase==OBJECTIF)
		{
			*secondeCase=CAISSE_OK;
			objectifRestant--;

			if (objectifRestant == 0){
				position.x = 0;
				position.y = 0;
				SDL_BlitSurface(menu, NULL, ecran, &position);
				SDL_Flip(ecran);
			}
		}
		else
			*secondeCase=CAISSE;
		if(*premiereCase==CAISSE_OK)
		{
			*premiereCase=OBJECTIF;
			objectifRestant++;
		}
		else
			*premiereCase=VIDE;
	}
	printf("objectif restant=%d\n", objectifRestant);
}

void jouer(SDL_Surface* ecran){

}

int chargerNiveau(int niveau[][NB_BLOC_HAUTEUR]){
	FILE* fichier=NULL;
	char ligneFichier[NB_BLOC_LARGEUR*NB_BLOC_HAUTEUR+1]={0};
	int i=0, j=0;

	fichier=fopen("niveau.lvl", "r");
	if (fichier==NULL)
		return 0;
	fgets(ligneFichier, NB_BLOC_LARGEUR*NB_BLOC_HAUTEUR+1, fichier);
	for(i=0; i<NB_BLOC_LARGEUR; i++){
		for(j=0; j<NB_BLOC_HAUTEUR; j++){
			switch(ligneFichier[(i*NB_BLOC_LARGEUR)+j]){
			case'0':
				niveau[j][i]=0;
				break;
			}
		}
	}

	return 0;
}


int main(int argc, char* argv[]){
	//SDL_Rect positionMenu;



	// Chargement de la vidéo et de l'audio
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
	{
        printf("erreur d'initialisation de la lib SDL\n");
        return -1;
	}

	printf("lib SDL iniitalisee avec succes!\n");
	ecran=SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_EnableKeyRepeat(100, 100);

	SDL_WM_SetIcon(IMG_Load("..\\caisse.jpg"), NULL);
	SDL_WM_SetCaption("Mario Sokoban", NULL);
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

	menu=IMG_Load("..\\menu.jpg");
	mur=IMG_Load("..\\mur.jpg");
	caisse=IMG_Load("..\\caisse.jpg");
	caisseOK=IMG_Load("..\\caisse_ok.jpg");
	objectif=IMG_Load("..\\objectif.png");
	mario[HAUT]=IMG_Load("..\\mario_bas.gif");
	mario[BAS]=IMG_Load("..\\mario_bas.gif");
	mario[GAUCHE]=IMG_Load("..\\mario_gauche.gif");
	mario[DROITE]=IMG_Load("..\\mario_droite.gif");
	position.x=0;
	position.y=0;

	marioActuel=mario[BAS];

	carte2[5][0]=VIDE;
	carte2[6][0]=VIDE;
	carte2[6][1]=VIDE;
	carte2[5][1]=VIDE;
	carte2[6][1]=VIDE;
	carte2[7][1]=VIDE;
	carte2[8][1]=VIDE;
	carte2[9][1]=VIDE;
	carte2[10][1]=VIDE;
	carte2[4][2]=VIDE;
	carte2[5][2]=VIDE;
	carte2[6][2]=VIDE;
	carte2[9][2]=VIDE;
	carte2[10][2]=VIDE;
	carte2[0][3]=VIDE;
	carte2[4][3]=VIDE;
	carte2[6][3]=VIDE;
	carte2[9][3]=VIDE;
	carte2[0][4]=VIDE;
    carte2[1][4]=VIDE;
	carte2[2][4]=VIDE;
	carte2[3][4]=VIDE;
	carte2[4][4]=VIDE;
	carte2[6][4]=VIDE;
	carte2[7][4]=VIDE;
	carte2[1][5]=VIDE;
	carte2[2][5]=VIDE;
	carte2[4][5]=VIDE;
	carte2[6][5]=VIDE;
	carte2[7][5]=VIDE;
	carte2[8][5]=VIDE;
	carte2[9][5]=VIDE;
	carte2[4][6]=VIDE;
	carte2[5][6]=VIDE;
	carte2[6][6]=VIDE;
	carte2[9][7]=VIDE;
	carte2[10][7]=VIDE;
	carte2[5][8]=VIDE;
	carte2[6][8]=VIDE;
	carte2[7][8]=VIDE;
	carte2[8][8]=VIDE;
	carte2[9][8]=VIDE;
	carte2[10][8]=VIDE;
	carte2[5][1]=MARIO;
	carte2[1][3]=OBJECTIF;
	carte2[2][3]=OBJECTIF;
	carte2[4][8]=OBJECTIF;
	carte2[5][4]=CAISSE;
	carte2[9][6]=CAISSE;
	carte2[9][4]=CAISSE;

	printf("Marc.Apres init carte\n");

	positionJoueur.x=5;
	positionJoueur.y=1;

	redessiner(ecran);

	printf("Marc.Apres flip\n .");


	pause(ecran);


	//SDL_FreeSurface(menu);
	SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
	return 0;
}
