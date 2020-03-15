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
    SDL_Renderer *renderer;/*Déclaration du renderer*/
    SDL_Rect rect = {20,20,100,100};/*On initialise un rectangle (position X, position Y, largeur, hauteur)*/
    SDL_Rect dim = {0,0,0,0};
    SDL_Surface * surface= NULL;/*On initialise un pointeur de type surface*/
    //SDL_Surface * surface2 = NULL;
    SDL_Texture * texture = NULL;
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
        //surface = SDL_CreateRGBSurface(0,200,200,32,0,0,0,0);/*On créer la surface*/
        surface = SDL_LoadBMP("image.bmp");
        //surface = SDL_GetWindowSurface(Window);
        //surface2 = SDL_CreateRGBSurface(0,surface->w,surface->h,32,0,0,0,0);
        //if((surface == NULL)|| (surface2 == NULL)) {
        if(surface == NULL){
        printf("Erreur lors de la surface a echoue : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,100,100);

//    SDL_SetRenderDrawColor(renderer,0,255,0,255);
//    SDL_SetRenderTarget(renderer,texture);
//    SDL_RenderFillRect(renderer, &rect);
//    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderPresent(renderer);

    //SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_QueryTexture(texture,NULL,NULL,&dim.w,&dim.h);
    SDL_RenderCopy(renderer, texture, NULL, &dim);
    //SDL_RenderPresent(renderer);



//        Uint32 color = SDL_MapRGB(surface->format,100,00,120); /*On applique un RGB sur la surface*/
//        Uint32 color2 = SDL_MapRGB(surface2->format,0,100,255);/*On applique un RGB sur la surface*/
//
//        SDL_FillRect(surface,NULL, color);/*On fill la surface */
//        SDL_FillRect(surface2,NULL, color2);/*On fill la surface */
//
//        SDL_UpdateWindowSurface(Window);/*On met à jour la fenêtre */
//
//        SDL_Delay(1000);
//
//        SDL_BlitSurface(surface2,NULL,surface,NULL);/*on fait une transition de surface*/
//        SDL_UpdateWindowSurface(Window);
//
//    /* Applique une couleur (RGB, alpha) */
//        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//
//    /* Applique la couleur */
//        SDL_RenderClear(renderer);
//
//    /* Affiche la couleur présente */
//        SDL_RenderPresent(renderer);
//
//
//        SDL_SetRenderDrawColor(renderer,0,0,0,255);
//        SDL_RenderDrawRect(renderer,&rect);/*On dessine le rectangle*/
//        SDL_RenderPresent(renderer);
//        SDL_Delay(1000);
//
//        SDL_RenderFillRect(renderer,&rect); /*Change la couleur*/
//        SDL_RenderPresent(renderer);
//        SDL_Delay(1000);
//
//        SDL_DrawCircle(renderer,200,100,40);/*On dessine le cercle*/
//        SDL_RenderPresent(renderer);
//        SDL_Delay(1000);
//
//        SDL_DrawFilledCircle(renderer,200,200,40);/*On remplit de couleur*/
//        SDL_RenderPresent(renderer);
//        SDL_Delay(1000);

    getchar();//Attendre une validation pour fermer la fenêtre
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);//On détruit la surface
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

