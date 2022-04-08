//
// Created by eii on 08/04/2022.
//

#include "main_view.h"



/* this function initialises the window and creates the texture/renderer for the menu
 * + allows to close it using the close tab button */

int Launch_view(Menu_windows * escape_menu)
{
    /* Initialisation bibliothèques */
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {   fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;    }
    if(0 == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
    {   fprintf(stderr, "Erreur IMG_Init : %s", SDL_GetError());
        goto Quit;    }


    int status = EXIT_FAILURE;
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;

    tmp = IMG_Load("../img/MENU.jpg");
    if (NULL == tmp) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        goto Quit;
    }
    if (0 != SDL_CreateWindowAndRenderer(escape_menu->SCREEN_WIDTH, escape_menu->SCREEN_HEIGHT, SDL_RENDERER_ACCELERATED, &escape_menu->window,&escape_menu->renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        goto Quit;
    }
    SDL_SetWindowTitle(escape_menu->window, "Launcher Menu");
    texture = SDL_CreateTextureFromSurface(escape_menu->renderer, tmp);
    SDL_FreeSurface(tmp); /* On libère la surface, on n’en a plus besoin */
    if (NULL == texture) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        goto Quit;
    }
    escape_menu->texture=SDL_CreateTexture(escape_menu->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,escape_menu->SCREEN_WIDTH,escape_menu->SCREEN_HEIGHT);
    fprintf(stderr,"ok1\n");
    SDL_SetRenderTarget(escape_menu->renderer,escape_menu->texture);
    // link btw window's renderer and texture
    fprintf(stderr,"ok2\n");
    SDL_RenderCopy(escape_menu->renderer,texture,NULL,NULL);
    //cpoy texture onto windows' one
    fprintf(stderr,"ok3\n");
    SDL_SetRenderTarget(escape_menu->renderer,NULL);
    //renderer doesn't point on anything anymore
    SDL_RenderCopy(escape_menu->renderer,escape_menu->texture,NULL,NULL);
    //final copy of windows' texture onto renderer
    SDL_RenderPresent(escape_menu->renderer);
    //renderer is all pretty and ready :)
    SDL_DestroyTexture(texture);
    //free texture

    int isRunning = 1;
    SDL_Event ev;

    while(isRunning==1){
        while(SDL_PollEvent(&ev)!=0){
            if (ev.type==SDL_QUIT) {
                isRunning =0;
            }
        }
        SDL_UpdateWindowSurface(escape_menu->window);
    }

    Quit:
    SDL_DestroyRenderer(escape_menu->renderer);
    SDL_DestroyWindow(escape_menu->window);
    SDL_DestroyTexture(escape_menu->texture);
    SDL_Quit();
    IMG_Quit();

    status = EXIT_SUCCESS;
    return status;
}
