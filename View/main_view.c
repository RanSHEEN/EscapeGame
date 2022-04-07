#include "main_view.h"


const int SCREEN_WIDTH = 1746;
const int SCREEN_HEIGHT = 984;

/* this function initialises the window and creates the texture/renderer for the menu
 * + allows to close it using the close tab button */

int Launch_view()
{
    /* Initialisation bibliothèques */
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Error SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    if(0 == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
    {
        fprintf(stderr, "Error IMG_Init : %s", SDL_GetError());
        goto Quit;
    }

    Menu_windows escape_menu;
    int status = EXIT_FAILURE;
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load("./img/MENU.jpg");
    if (NULL == tmp) {
        fprintf(stderr, "Error IMG_load: %s", SDL_GetError());
        goto Quit;
    }

    if (0 != SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_RENDERER_ACCELERATED, & escape_menu.window,& escape_menu.renderer))
    {
        fprintf(stderr, "Error SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        goto Quit;
    }

    SDL_SetWindowTitle(escape_menu.window,"Launcher Menu");
    texture = SDL_CreateTextureFromSurface(escape_menu.renderer, tmp);
    SDL_FreeSurface(tmp);
    /* On libère la surface, on n’en a plus besoin */
    if (NULL == texture) {
        fprintf(stderr, "Error SDL_CreateTextureFromSurface : %s", SDL_GetError());
        goto Quit;
    }

    SDL_RenderCopy(escape_menu.renderer,texture,NULL,NULL);
    SDL_RenderPresent(escape_menu.renderer);

    //personWalk(texture,escape_menu.renderer); //try personnage display (work !)

    //SDL_Delay(10000);

    int isRunning = 1;
    SDL_Event ev;

    while(isRunning==1){
        while(SDL_PollEvent(&ev)!=0){
            if (ev.type==SDL_QUIT) {
                isRunning =0;
            }
        }
        SDL_UpdateWindowSurface(escape_menu.window);
    }



    Quit:
        SDL_DestroyRenderer(escape_menu.renderer);
        SDL_DestroyWindow(escape_menu.window);
        SDL_Quit();
        IMG_Quit();

   status = EXIT_SUCCESS;
   return status;
}

int Person_view()
{
    /* Initialisation bibliothèques */
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {   fprintf(stderr, "Error SDL_Init : %s\n", SDL_GetError());
        goto Quit;    }
    if(0 == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
    {   fprintf(stderr, "Error IMG_Init : %s\n", SDL_GetError());
        goto Quit;    }

    Menu_windows person_window;
    int status = EXIT_FAILURE;
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;

    personWalk(texture, person_window.renderer);

    int isRunning = 1;
    SDL_Event ev;

    while(isRunning==1){
        while(SDL_PollEvent(&ev)!=0){
            if (ev.type==SDL_QUIT) {
                isRunning =0;
            }
        }
        SDL_UpdateWindowSurface(person_window.window);
    }


Quit:
    SDL_DestroyRenderer(person_window.renderer);
    SDL_DestroyWindow(person_window.window);
    SDL_Quit();
    IMG_Quit();

    status = EXIT_SUCCESS;
    return status;
}
