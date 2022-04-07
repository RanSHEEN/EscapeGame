//
// Created by gracesheenxinran on 4/7/22.
//

#include "personnage.h"

const int WALK_PICTURE_NUMBER = 8;
const int SPEED = 90;

void personStatic(SDL_Texture *texture, SDL_Renderer *rend) {
    SDL_Rect rect, walks[WALK_PICTURE_NUMBER];
    SDL_Surface * img = IMG_Load("walkTest.png");
    if (img == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    texture = SDL_CreateTextureFromSurface(rend, img);

    rect.x = 0;
    rect.y = 0;
    rect.h = img->h;
    rect.w = img->w / WALK_PICTURE_NUMBER;

    walks[1].w = img->w / WALK_PICTURE_NUMBER;
    walks[1].h = img->h;
    walks[1].x = walks[1].w;
    walks[1].y = 0;
}

void personWalk(SDL_Texture *texture, SDL_Renderer *rend) {
    SDL_Rect rect, walks[WALK_PICTURE_NUMBER];
    SDL_Surface * img = IMG_Load("./img/walkTest.png");
    if (img == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    texture = SDL_CreateTextureFromSurface(rend, img);

    rect.x = 0;
    rect.y = 0;
    rect.h = img->h;
    rect.w = img->w / WALK_PICTURE_NUMBER;

    int i;
    for (i = 0; i<WALK_PICTURE_NUMBER; i++)
    {
        walks[i].w = img->w / WALK_PICTURE_NUMBER;
        walks[i].h = img->h;
        walks[i].x = i*walks[i].w;
        walks[i].y = 0;
    }

    int isRunning = 1;
    SDL_Event event;
    while (isRunning==1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = 0;
            }
        }
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, texture, &walks[i], &rect);
        i = (i + 1) % 8;
        //rect.x = (rect.x + 5) % (rect.w * 8); //situation go right
        SDL_RenderPresent(rend); //situation state
        SDL_Delay(SPEED);
    }

}
