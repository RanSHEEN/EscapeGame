//
// Created by eii on 08/04/2022.
//

#include "main_view.h"



/* this function initialises the window and creates the texture/renderer for the menu
 * + allows to close it using the close tab button */

int init_game(Windows  * game_window){

    int status = EXIT_FAILURE;

    if (0 != SDL_CreateWindowAndRenderer(1746,984,SDL_RENDERER_ACCELERATED,&game_window->window,&game_window->renderer))
    {
        fprintf(stderr, "error SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetWindowPosition(game_window->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    game_window->texture=SDL_CreateTexture(game_window->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,1746,984);

    if(NULL== game_window->texture){
        fprintf(stderr, "error SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    game_window->Type=Rules;
    get_Tittle (game_window->Type , game_window->title);
    SDL_SetWindowTitle(game_window->window, game_window->title);

    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load("img/gaming.jpg");
    if (NULL == tmp) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(game_window->renderer);
        SDL_DestroyWindow(game_window->window);
        SDL_DestroyTexture(game_window->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(game_window->renderer, tmp);
    SDL_FreeSurface(tmp); /* On libère la surface, on n’en a plus besoin */
    if (NULL == texture) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        SDL_DestroyRenderer(game_window->renderer);
        SDL_DestroyWindow(game_window->window);
        SDL_DestroyTexture(game_window->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
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


    status = EXIT_SUCCESS;
    return status;
}

