
#include "main_view.h"


const int SCREEN_WIDTH = 1746;
const int SCREEN_HEIGHT = 984;

/* this function initialises the window and creates the texture/renderer for the menu  */

int main()
{
    /* Initialisation bibliothèques */
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {   fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;    }
    if(0 == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
    {   fprintf(stderr, "Erreur IMG_Init : %s", SDL_GetError());
        goto Quit;    }

    Menu_windows escape_menu;
    int status = EXIT_FAILURE;
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load("img/MENU.jpg");
    if (NULL == tmp) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        goto Quit;
    }

    if (0 != SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_RENDERER_ACCELERATED, & escape_menu.window,& escape_menu.renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        goto Quit;
    }

    texture = SDL_CreateTextureFromSurface(escape_menu.renderer, tmp);
    SDL_FreeSurface(tmp); /* On libère la surface, on n’en a plus besoin */
    if (NULL == texture) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        goto Quit;
    }

    SDL_RenderCopy(escape_menu.renderer,texture,NULL,NULL);
    SDL_RenderPresent(escape_menu.renderer);
    while(1){   }

    Quit:
        SDL_DestroyRenderer(escape_menu.renderer);
        SDL_DestroyWindow(escape_menu.window);
        SDL_Quit();
        IMG_Quit();

   status = EXIT_SUCCESS;


    return status;
}