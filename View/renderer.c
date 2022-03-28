//
// Created by gracesheenxinran on 3/17/22.
//

#include "renderer.h"


int initialRenderer(SDL_Window *window, SDL_Renderer *ren)
{
    int *argcp;
    char **argv;
    unsigned int mode;

    if(ren == NULL)
    {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error.\n");
        return 1;
    } else {
        glutInit(*argcp, **argv);
        glutInitDisplayMode(mode);
        return 0;
    }
}

int clearRenderer(SDL_Renderer *ren)
{
    if(0 != SDL_RenderClear(ren))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        return -1;
    }
    SDL_RenderClear(ren);
}

int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    if(SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;
}






