#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    /**Variable**/
    SDL_Window *Window = NULL;/*On initialise la fen�tre*/
    SDL_Renderer* renderer;/*D�claration du renderer*/
    SDL_Rect rect = {20,20,100,100};/*On initialise un rectangle (position X, position Y, largeur, hauteur)*/
    SDL_Point point = {20,40};/*On initialise point position X, position Y*/

    /**Initialisation**/
    if(0 != SDL_Init(SDL_INIT_EVERYTHING))/* initialisation*/
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());/*si la SDL ne fonctionne pas ,on re�oit un message d'erreur*/
        return EXIT_FAILURE;
    }
    /**Ouverture de la fen�tre**/
    Window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              300,300, SDL_WINDOW_SHOWN);

    /**Fenetre Error**/
    if(NULL == Window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Cr�ation du renderer
    renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    /**Renderer Error**/
    if(NULL == renderer)
    {
    printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
    return EXIT_FAILURE;
    }

    getchar();//Attendre une validation pour fermer la fen�tre
    SDL_DestroyRenderer(renderer); // Destruction du renderer et de la fen�tre :
    SDL_DestroyWindow(Window); //Supprime la fen�tre*

    /**Quitter**/
    SDL_Quit();
    return EXIT_SUCCESS;
}

