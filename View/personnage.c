//
// Created by gracesheenxinran on 4/7/22.
//

//
#include "main_view.h"


int init_character (View_app * app){
    app->Robot.SPEED = 60;
    app->Robot.WALK_PICTURE_NUMBER =8;
    app->Robot.anim_state=0;
    app->Robot.Position.x=900;
    app->Robot.Position.y=500;

    //get image robot right
    SDL_Surface * Robot_right = IMG_Load("./img/RobotWalkRight.png");
    if (Robot_right == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    //init rect in which robot exists
    app->Robot.Position.h=Robot_right->h;
    app->Robot.Position.w=Robot_right->w / app->Robot.WALK_PICTURE_NUMBER;

    //creates robot right texture in the rectangle
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app->Game.renderer, Robot_right);
    if (texture == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_SetRenderTarget(app->Game.renderer,app->Robot.move_R);
    SDL_RenderCopy(app->Game.renderer,texture,NULL,NULL);
    SDL_SetRenderTarget(app->Game.renderer,NULL);
    SDL_Rect rect={0,0,Robot_right->w/app->Robot.WALK_PICTURE_NUMBER,Robot_right->h};

    //defines Robot walks r rectangle
    for (int i = 0; i<app->Robot.WALK_PICTURE_NUMBER; i++)
    {
        app->Robot.walks_R[i].w = Robot_right->w / app->Robot.WALK_PICTURE_NUMBER;
        app->Robot.walks_R[i].h = Robot_right->h;
        app->Robot.walks_R[i].x = rect.x + i*app->Robot.walks_R[i].w;
        app->Robot.walks_R[i].y = 0;
    }

    SDL_FreeSurface(Robot_right);
    SDL_DestroyTexture(texture);


    SDL_Surface * Robot_still_FB = IMG_Load("./img/RobotWalkFront.png");
    if (Robot_still_FB == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetRenderTarget(app->Game.renderer,app->Robot.move_F);
    SDL_RenderCopy(app->Game.renderer,texture,NULL,NULL);
    SDL_SetRenderTarget(app->Game.renderer,NULL);
    SDL_Rect rect2={0,0,Robot_still_FB->w/app->Robot.WALK_PICTURE_NUMBER,Robot_still_FB->h};

    //defines Robot walks fbs rectangle
    for (int i = 0; i<app->Robot.WALK_PICTURE_NUMBER; i++)
    {
        app->Robot.walks_F[i].w = Robot_still_FB->w / app->Robot.WALK_PICTURE_NUMBER;
        app->Robot.walks_F[i].h = Robot_still_FB->h;
        app->Robot.walks_F[i].x = rect2.x + i*app->Robot.walks_F[i].w;
        app->Robot.walks_F[i].y = 0;
    }

    SDL_FreeSurface(Robot_right);
    SDL_DestroyTexture(texture);


    SDL_Surface * Robot_left = IMG_Load("./img/RobotWalkLeft.png");
    if (Robot_left == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetRenderTarget(app->Game.renderer,app->Robot.move_L);
    SDL_RenderCopy(app->Game.renderer,texture,NULL,NULL);
    SDL_SetRenderTarget(app->Game.renderer,NULL);
    SDL_Rect rect3={0,0,Robot_left->w/app->Robot.WALK_PICTURE_NUMBER,Robot_left->h};

    //defines Robot walks fbs rectangle
    for (int i = 0; i<app->Robot.WALK_PICTURE_NUMBER; i++)
    {
        app->Robot.walks_L[i].w = Robot_still_FB->w / app->Robot.WALK_PICTURE_NUMBER;
        app->Robot.walks_L[i].h = Robot_still_FB->h;
        app->Robot.walks_L[i].x = rect3.x + i*app->Robot.walks_L[i].w;
        app->Robot.walks_L[i].y = 0;
    }
    SDL_FreeSurface(Robot_right);
    SDL_DestroyTexture(texture);
return EXIT_SUCCESS;
}


