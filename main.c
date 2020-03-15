#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

void SDL_DrawOctants(SDL_Renderer *renderer, int nCentreX,int nCentreY, int x, int y);
void SDL_DrawCircle(SDL_Renderer * renderer, int nCentreX, int nCentreY, int nRadius);
void SDL_DrawFilledCircle(SDL_Renderer* renderer, int nCentreX,int nCentreY, int nRadius);

int main(int argc, char *argv[])
{
    /**Variable**/
    SDL_Window *Window = NULL;/*On initialise la fenêtre*/
    SDL_Renderer* renderer;/*Déclaration du renderer*/
    SDL_Rect rect = {20,20,100,100};/*On initialise un rectangle (position X, position Y, largeur, hauteur)*/
    //SDL_Point point = {20,40};/*On initialise point position X, position Y*/

    /**Initialisation**/
    if(0 != SDL_Init(SDL_INIT_EVERYTHING))/* initialisation*/
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());/*si la SDL ne fonctionne pas ,on reçoit un message d'erreur*/
        return EXIT_FAILURE;
    }
    /**Ouverture de la fenêtre**/
    Window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              400,400, SDL_WINDOW_SHOWN);

    /**Fenetre Error**/
    if(NULL == Window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    /**Renderer Error**/
    if(NULL == renderer)
    {
    printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
    return EXIT_FAILURE;
    }

    /* Applique une couleur (RGB, alpha) */
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    /* Applique la couleur */
        SDL_RenderClear(renderer);

    /* Affiche la couleur présente */
        SDL_RenderPresent(renderer);


        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderDrawRect(renderer,&rect);/*On dessine le rectangle*/
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);

        SDL_RenderFillRect(renderer,&rect); /*Change la couleur*/
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);

        SDL_DrawCircle(renderer,200,100,40);/*On dessine le cercle*/
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);

        SDL_DrawFilledCircle(renderer,200,200,40);/*On remplit de couleur*/
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);

    getchar();//Attendre une validation pour fermer la fenêtre
    SDL_DestroyRenderer(renderer); // Destruction du renderer et de la fenêtre :
    SDL_DestroyWindow(Window); //Supprime la fenêtre*

    /**Quitter**/
    SDL_Quit();
    return EXIT_SUCCESS;
}

/** octants de l'algorime de Bresenhams pour le circle**/
void SDL_DrawOctants(SDL_Renderer *renderer, int nCentreX,int nCentreY, int x, int y) {
    SDL_RenderDrawPoint(renderer,nCentreX+x,nCentreY+y);
    SDL_RenderDrawPoint(renderer,nCentreX-x,nCentreY+y);
    SDL_RenderDrawPoint(renderer,nCentreX+x,nCentreY-y);
    SDL_RenderDrawPoint(renderer,nCentreX-x,nCentreY-y);
    SDL_RenderDrawPoint(renderer,nCentreX+y,nCentreY+x);
    SDL_RenderDrawPoint(renderer,nCentreX-y,nCentreY+x);
    SDL_RenderDrawPoint(renderer,nCentreX+y,nCentreY-x);
    SDL_RenderDrawPoint(renderer,nCentreX-y,nCentreY-x);
}

/**Trace un cercle vide**/
void SDL_DrawCircle(SDL_Renderer * renderer, int nCentreX, int nCentreY, int nRadius) {
    int x = 0;
    int y = 0;
    int d;
    d = 3 - 2*nRadius;
    y = nRadius;

    SDL_DrawOctants(renderer,nCentreX,nCentreY,x,y);
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d +  4*(x-y)+10;
        } else {
            d = d + 4*x + 6;
        }
        SDL_DrawOctants(renderer,nCentreX,nCentreY,x,y);
    }
}

/**Trace un cercle plein**/
void SDL_DrawFilledCircle(SDL_Renderer* renderer, int nCentreX,int nCentreY, int nRadius){
    int x = 0;
    int y = 0;
    int d;
    d = 3 - 2*nRadius;
    y = nRadius;

    SDL_DrawOctants(renderer,nCentreX,nCentreY,x,y);

    //Lignes horizontales entre les octants
    SDL_RenderDrawLine(renderer,nCentreX - x,nCentreY - y, nCentreX + x,nCentreY - y);
    SDL_RenderDrawLine(renderer,nCentreX - y,nCentreY + x, nCentreX + y,nCentreY + x);
    SDL_RenderDrawLine(renderer,nCentreX - y,nCentreY - x, nCentreX + y,nCentreY - x);
    SDL_RenderDrawLine(renderer,nCentreX - x,nCentreY + y, nCentreX + x,nCentreY + y);

    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d +  4*(x-y)+10;
        } else {
            d = d + 4*x + 6;
        }
        SDL_DrawOctants(renderer,nCentreX,nCentreY,x,y);

        //Lignes horizontales entre les octants
        SDL_RenderDrawLine(renderer,nCentreX - x,nCentreY - y, nCentreX + x,nCentreY - y);
        SDL_RenderDrawLine(renderer,nCentreX - y,nCentreY + x, nCentreX + y,nCentreY + x);
        SDL_RenderDrawLine(renderer,nCentreX - y,nCentreY - x, nCentreX + y,nCentreY - x);
        SDL_RenderDrawLine(renderer,nCentreX - x,nCentreY + y, nCentreX + x,nCentreY + y);
    }
}

