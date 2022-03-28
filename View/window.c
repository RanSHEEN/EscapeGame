//
// Created by gracesheenxinran on 3/17/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "window.h"

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

b32 RUNNING = 1;

void setWindowTitle(SDL_Window *window, SDL_Event e){
    const char *titles[] = {
            "Start","End"
    };

    // Enter the main loop. Press any key or hit the x to exit.
    for( ; e.type!=SDL_QUIT && e.type!=SDL_KEYDOWN; SDL_PollEvent(&e)){
        static int i = 0, t = 0;

        if(!(++t%9)){ // every 9th frame...
            // loop through the array of titles
            SDL_SetWindowTitle(window, titles[i]);
            if(++i >= sizeof(titles)/sizeof(titles[0])) i = 0;
        }
    }
}

void visibilityWindow(SDL_Window *window){
    switch (RUNNING) {
        case SDL_WINDOW_HIDDEN:
            SDL_HideWindow(window);
            break;
        case SDL_WINDOW_SHOWN:
            SDL_ShowWindow(window);
            break;
    }
}

void fullScreen(SDL_Window *window, SDL_Event e){
    b32 FullScreen = 0;
    u32 WindowFlags = SDL_WINDOW_OPENGL;

    while (RUNNING) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        RUNNING = 0;
                        break;
                    case 'f':
                        FullScreen = !FullScreen;
                        if (FullScreen) {
                            SDL_SetWindowFullscreen(window, WindowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                        } else {
                            SDL_SetWindowFullscreen(window, WindowFlags);
                        }
                        break;
                    default:
                        break;
                }
            } else if (e.type == SDL_QUIT) {
                RUNNING = 0;
            }
        }
    }
}

void restoreWindow(SDL_Window *window){
    SDL_RestoreWindow(window);
}
