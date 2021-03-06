#include "fmap.h"
#include "fevent.h"

#define LARGEUR_FENETRE 500
#define HAUTEUR_FENETRE 500
#define MOVESPEED 1

void MoveMap(Map* m,Input* in)
{
	if (in->key[SDLK_LEFT])
		m->xscroll-=MOVESPEED;
	if (in->key[SDLK_RIGHT])
		m->xscroll+=MOVESPEED;
	if (in->key[SDLK_UP])
		m->yscroll-=MOVESPEED;
	if (in->key[SDLK_DOWN])
		m->yscroll+=MOVESPEED;
	// limitation
	if (m->xscroll<0)
		m->xscroll=0;
	if (m->yscroll<0)
		m->yscroll=0;
	if (m->xscroll>m->nbtiles_largeur_monde*m->LARGEUR_TILE-m->largeur_fenetre-1)
		m->xscroll=m->nbtiles_largeur_monde*m->LARGEUR_TILE-m->largeur_fenetre-1;
	if (m->yscroll>m->nbtiles_hauteur_monde*m->HAUTEUR_TILE-m->hauteur_fenetre-1)
		m->yscroll=m->nbtiles_hauteur_monde*m->HAUTEUR_TILE-m->hauteur_fenetre-1;
}

int main(int argc,char** argv)
{
	SDL_Surface* screen;
	Map* m;
	Input I;
	InitEvents(&I);
	SDL_Init(SDL_INIT_VIDEO);		// prepare SDL
	screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	m = ChargerMap("level2.txt",LARGEUR_FENETRE,HAUTEUR_FENETRE);
	while(!I.key[SDLK_ESCAPE] && !I.quit)
	{
		UpdateEvents(&I);
		MoveMap(m,&I);
		AfficherMap(m,screen);
		SDL_Flip(screen);
		SDL_Delay(1);
	}
	LibererMap(m);
	SDL_Quit();
	return 0;
}
