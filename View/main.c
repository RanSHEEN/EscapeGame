#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int SDL_Init(Uint32 flags);

int main() {
    SDL_Window *window = NULL;

    SDL_Surface *screenSurface = NULL;

    // initialize SDL
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        // create a window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            // get the surface of the window
            screenSurface = SDL_GetWindowSurface(window);

            // fill the surface with white color
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            // update the window
            SDL_UpdateWindowSurface(window);

            // wait 10 seconds
            SDL_Delay(10000);
        }
    }

    // create a renderer
    SDL_Renderer *ren = SDL_CreateRenderer(window , -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == NULL)
    {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error.\n");
        return 1;
    }

    // load a bmp image
    SDL_Surface *bmp = SDL_LoadBMP("hello.bmp");
    if(bmp == NULL)
    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(window);
        printf("SDL_LoadBMP Error.\n");
        SDL_Quit();
        return 1;
    }

    // load the texture
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == NULL){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(window);
        printf("SDL_CreateTextureFromSurface Error.\n");
        SDL_Quit();
        return 1;
    }

    // destroy
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    // quit SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
