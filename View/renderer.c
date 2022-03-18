//
// Created by gracesheenxinran on 3/17/22.
//

#include "renderer.h"


int initialRenderer(SDL_Window *window, SDL_Renderer *ren){
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







