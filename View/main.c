#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include <SDL2/SDL_opengl.h>

#include "window.h"
#include "renderer.h"
#include "texture.h"
#include "event.h"

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main() {
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
    SDL_Event e;

//    b32 Running = 1;
//    b32 FullScreen = 0;
//    u32 WindowFlags = SDL_WINDOW_OPENGL;

    // initialize SDL
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    } else {
        // create a window
        window = SDL_CreateWindow("Escape Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            // get the surface of the window
            screenSurface = SDL_GetWindowSurface(window);

            // fill the surface with white color
            SDL_FillRect(screenSurface,NULL,SDL_MapRGB(screenSurface->format,0xFF,0xFF,0xFF));

            // update the window
            SDL_UpdateWindowSurface(window);

            // wait 10 seconds
            SDL_Delay(10000);
        }
    }

//    setWindowTitle(window,e);

    // create a renderer
    SDL_Renderer *ren = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    initialRenderer(window,ren);

    // load the texture
    SDL_Surface *bmp = SDL_LoadBMP("test.bmp");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren,bmp);
    SDL_FreeSurface(bmp);
    if (tex == NULL) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(window);
        printf("SDL_CreateTextureFromSurface Error.\n");
        SDL_Quit();
        return 1;
    }

    SDL_Rect rect = {50,50,SCREEN_WIDTH,SCREEN_HEIGHT};

    /* here not compiled successfully */
//    initialTexture(ren,tex,rect);
//    circle(e,ren,tex,rect);
//
//    // load a bmp image
//    loadImage(ren,tex,bmp);

    // destroy
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    // quit SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}