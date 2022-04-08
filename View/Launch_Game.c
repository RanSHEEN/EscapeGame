//
// Created by eii on 08/04/2022.
//

#include "main_view.h"



/* this function initialises the window and creates the texture/renderer for the menu
 * + allows to close it using the close tab button */

int Game_Window(Menu_windows  * game_window){

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
    if (0 != SDL_CreateWindowAndRenderer(game_window->SCREEN_WIDTH,game_window->SCREEN_HEIGHT,SDL_RENDERER_ACCELERATED,&game_window->window,&game_window->renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        goto Quit;
    }

    SDL_SetWindowTitle(game_window->window, "Escape this Room !");
    texture = SDL_CreateTextureFromSurface(game_window->renderer, tmp);
    SDL_FreeSurface(tmp); /* On libère la surface, on n’en a plus besoin */
    if (NULL == texture) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        goto Quit;
    }
    game_window->texture=SDL_CreateTexture(game_window->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,game_window->SCREEN_WIDTH,game_window->SCREEN_HEIGHT);
    SDL_SetRenderTarget(game_window->renderer,game_window->texture);
    // link btw window's renderer and texture
    SDL_RenderCopy(game_window->renderer,texture,NULL,NULL);
    //cpoy texture onto windows' one
    SDL_DestroyTexture(texture);
    //free texture
    SDL_SetRenderTarget(game_window->renderer,NULL);
    //renderer doesn't point on anything anymore
    SDL_RenderCopy(game_window->renderer,game_window->texture,NULL,NULL);
    //final copy of windows' texture onto renderer
    SDL_RenderPresent(game_window->renderer);
    //renderer is all pretty and ready :)

    int isRunning = 1;
    SDL_Event ev;

    while(isRunning==1){
        while(SDL_PollEvent(&ev)!=0){
            if (ev.type==SDL_QUIT) {
                isRunning =0;
            }
        }
        SDL_UpdateWindowSurface(game_window->window);
    }

    Quit:
    SDL_DestroyRenderer(game_window->renderer);
    SDL_DestroyWindow(game_window->window);
    SDL_DestroyTexture(game_window->texture);
    SDL_Quit();
    IMG_Quit();
    status = EXIT_SUCCESS;
    return status;
}
