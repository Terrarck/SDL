#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

int main(int argc, char *argv[])
{
    SDL_Window *pWindow=NULL;
    SDL_Renderer *pRenderer=NULL;
    SDL_Texture *pTexture=NULL;
    SDL_Surface *image = NULL;

    SDL_Rect rect = {0,0,500,500},src= {0,0,8,8};

    SDL_SetRenderDrawColor(pRenderer,255,255,255,1);
    SDL_RenderClear(pRenderer);

    pWindow = SDL_CreateWindow("SDL2",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 800, 400, SDL_WINDOW_RESIZABLE);

    image = IMG_Load("image2.png");

    if (pWindow == NULL)
    {
        printf("Erreur lors de la creation d'une fenetre : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (pRenderer == NULL)
    {
        printf("Erreur lors de la création du render : %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    pTexture = SDL_CreateTextureFromSurface(pRenderer,image);

    for (int i=0; i<20; i++)
    {
        src.x = i*8;
        SDL_RenderCopy(pRenderer,pTexture,&src,&rect);

        SDL_RenderPresent(pRenderer);

        SDL_Delay(1000);
    }

    SDL_Quit();
    return 0;

}
