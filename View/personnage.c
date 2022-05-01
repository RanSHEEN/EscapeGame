//
// Created by gracesheenxinran on 4/7/22.
//

//
#include "personnage.h"

const int WALK_PICTURE_NUMBER = 8;
const int SPEED = 60;


void personStatic(SDL_Renderer *rend) {
    SDL_Rect rect, walks[WALK_PICTURE_NUMBER];
    SDL_Surface * map = IMG_Load("./img/background.jpg");
    SDL_Surface * img = IMG_Load("./img/RobotWalkRight.png");
    if (map == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend,map);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, img);

    rect.x = 0;
    rect.y = 0;
    rect.h = img->h;
    rect.w = img->w / WALK_PICTURE_NUMBER;

    walks[1].w = img->w / WALK_PICTURE_NUMBER;
    walks[1].h = img->h;
    walks[1].x = walks[1].w;
    walks[1].y = 0;
}

void personWalkRight(SDL_Renderer *rend) {
    SDL_Rect rect, walks[WALK_PICTURE_NUMBER];
    SDL_Surface * map = IMG_Load("./img/background.jpg");
    SDL_Surface * img = IMG_Load("./img/RobotWalkRight.png");
    if (map == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend,map);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, img);

    rect.x = 0;
    rect.y = 0;
    rect.h = img->h;
    rect.w = img->w / WALK_PICTURE_NUMBER;

    int i;
    for (i = 0; i<WALK_PICTURE_NUMBER; i++)
    {
        walks[i].w = img->w / WALK_PICTURE_NUMBER;
        walks[i].h = img->h;
        walks[i].x = rect.x + i*walks[i].w;
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
        SDL_RenderCopy(rend, tex, NULL, NULL);
        SDL_RenderCopy(rend, texture, &walks[i], &rect);
        i = (i + 1) % WALK_PICTURE_NUMBER;
        rect.x = (rect.x + 5) % (rect.w * WALK_PICTURE_NUMBER); //situation go right
        SDL_RenderPresent(rend); //situation state
        SDL_Delay(SPEED);
    }
}

void personWalkLeft(SDL_Renderer *rend) {
    SDL_Rect rect, walks[WALK_PICTURE_NUMBER];
    SDL_Surface * map = IMG_Load("./img/background.jpg");
    SDL_Surface * img = IMG_Load("./img/RobotWalkLeft.png");
    if (map == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend,map);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, img);

    rect.x = 200;
    rect.y = 200;
    rect.h = img->h;
    rect.w = img->w / WALK_PICTURE_NUMBER;

    int i;
    for (i = 0; i<WALK_PICTURE_NUMBER; i++)
    {
        walks[i].w = img->w / WALK_PICTURE_NUMBER;
        walks[i].h = img->h;
        walks[i].x = rect.x + i*walks[i].w;
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
        SDL_RenderCopy(rend, tex, NULL, NULL);
        SDL_RenderCopy(rend, texture, &walks[i], &rect);
        i = (i + 1) % 8;
        rect.x = (rect.x - 5) % (rect.w * WALK_PICTURE_NUMBER); //situation go left
        SDL_RenderPresent(rend); //situation state
        SDL_Delay(SPEED);
    }
}

void personWalkUp(SDL_Renderer *rend) {
    SDL_Rect rect, walks[WALK_PICTURE_NUMBER];
    SDL_Surface * map = IMG_Load("./img/background.jpg");
    SDL_Surface * img = IMG_Load("./img/walkTest.png");
    if (map == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend,map);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, img);

    rect.x = 900;
    rect.y = 900;
    rect.h = img->h;
    rect.w = img->w / WALK_PICTURE_NUMBER;

    int i;
    for (i = 0; i<WALK_PICTURE_NUMBER; i++)
    {
        walks[i].w = img->w / WALK_PICTURE_NUMBER;
        walks[i].h = img->h;
        walks[i].x = rect.x - i*walks[i].w;
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
        SDL_RenderCopy(rend, tex, NULL, NULL);
        SDL_RenderCopy(rend, texture, &walks[i], &rect);
        i = (i + 1) % 8;
        rect.y = (rect.y - 5) % (rect.h * WALK_PICTURE_NUMBER); //situation go up
        SDL_RenderPresent(rend); //situation state
        SDL_Delay(SPEED);
    }
}

void personWalkDown(SDL_Renderer *rend){
    SDL_Rect rect, walks[WALK_PICTURE_NUMBER];
    SDL_Surface * map = IMG_Load("./img/background.jpg");
    SDL_Surface * img = IMG_Load("./img/RobotWalkFront.png");
    if (map == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend,map);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, img);

    rect.x = 0;
    rect.y = 0;
    rect.h = img->h;
    rect.w = img->w / WALK_PICTURE_NUMBER;

    int i;
    for (i = 0; i<WALK_PICTURE_NUMBER; i++)
    {
        walks[i].w = img->w / WALK_PICTURE_NUMBER;
        walks[i].h = img->h;
        //walks[i].x = rect.x - i*walks[i].w;
        walks[i].x = rect.x - i;
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
        SDL_RenderCopy(rend, tex, NULL, NULL);
        SDL_RenderCopy(rend, texture, &walks[i], &rect);
        i = (i + 1) % 8;
        rect.y = (rect.y + 1) % (rect.h * WALK_PICTURE_NUMBER); //situation go down
        SDL_RenderPresent(rend); //situation state
        SDL_Delay(SPEED/10);
    }
}
