//
// Created by gracesheenxinran on 3/27/22.
//

#include <stdbool.h>
#include "event.h"

int circle(SDL_Event e, SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect rect) {
    bool quit = false;
    int sx = 0, sy = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    sx = e.button.x + rect.x;
                    sy = e.button.y + rect.y;
                    break;
                case SDL_MOUSEMOTION:
                    if (e.motion.state & SDL_BUTTON_LMASK) {
                        rect.x = e.motion.x - sx;
                        rect.y = e.motion.y - sy;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_LEFT) {
                        rect.x -= 10;
                        printf("SDLK_LEFT...");
                    } else if (e.key.keysym.sym == SDLK_RIGHT) {
                        printf("SDLK_RIGHT...");
                        rect.x += 10;
                    } else if (e.key.keysym.sym == SDLK_UP) {
                        printf("SDLK_UP...");
                        rect.w += 10;
                        rect.h += 10;
                    } else if (e.key.keysym.sym == SDLK_DOWN) {
                        printf("SDLK_DOWN...");
                        rect.w -= 10;
                        rect.h -= 10;
                    }
                    printf("scancode=%d\n", e.key.keysym.scancode);
                    break;
                case SDL_MOUSEWHEEL:
                    if (e.wheel.y > 0) {
                        rect.h *= 1.1;
                        rect.w *= 1.1;
                    }
                    if (e.wheel.y < 0) {
                        rect.w /= 1.1;
                        rect.h /= 1.1;
                    }
                    break;
            }
        }

        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, &rect);
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
}