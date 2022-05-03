//
// Created by kuilong on 4/7/22.
//

#include <stdio.h>
#include "SDL2/SDL.h"
#include "controller.h"

int Launch_event(SDL_Event e) {
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    printf("Click\n ");
                    break;
                /*case SDL_MOUSEMOTION:
                    if (e.motion.state & SDL_BUTTON_LMASK) {
                        rect.x = e.motion.x - sx;
                        rect.y = e.motion.y - sy;
                    }
                    break;
                */
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_LEFT) {
                        printf("SDLK_LEFT...personnage move left... ");
                    } else if (e.key.keysym.sym == SDLK_RIGHT) {
                        printf("SDLK_RIGHT...personnage move right...");
                    } else if (e.key.keysym.sym == SDLK_UP) {
                        printf("SDLK_UP...personnage move up...");
                    } else if (e.key.keysym.sym == SDLK_DOWN) {
                        printf("SDLK_DOWN...personnage move down...");
                    }else if (e.key.keysym.sym == SDLK_SPACE) {
                        printf("SDLK_SPACE...read the information");
                        printf("display the information");
                    }
                    printf("scancode=%d\n", e.key.keysym.scancode);
                    break;
                /*case SDL_MOUSEWHEEL:
                    if (e.wheel.y > 0) {
                        //rect.h *= 1.1;
                        //rect.w *= 1.1;
                    }
                    if (e.wheel.y < 0) {
                        //rect.w /= 1.1;
                        //rect.h /= 1.1;
                    }
                    break;
                */
            }
        }
    }
    return quit;
}