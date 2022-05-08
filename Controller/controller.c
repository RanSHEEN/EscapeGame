
// Created by Margot on 06/04/2022.


#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include "../View/main_view.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

int move_robot(View_app *view_app) {
    SDL_Point point;
    int isRunning = 1;
    int status = EXIT_FAILURE;
    SDL_Event ev;
    //Load Chunk of move
    Mix_Chunk *moveSound = Mix_LoadWAV("music/Move_sound.wav");

    if (init_character(view_app) != EXIT_SUCCESS) {
        fprintf (stderr, "failed init character \n");
        return EXIT_FAILURE;
    }
    while (isRunning == SDL_TRUE) {
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_KEYDOWN:
                    if (ev.key.keysym.sym == SDLK_LEFT) {
                        if (view_app->Robot.Position.x >= 0) {
                            // play Chunk of move , same for after
                            Mix_PlayChannel(-1,moveSound,-1);
                            personWalkLeft(view_app);
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_RIGHT) {
                     if (view_app->Robot.Position.x <= 1164) {
                         Mix_PlayChannel(-1,moveSound,-1);
                         personWalkRight(view_app);
                     }

                    }
                    else if (ev.key.keysym.sym == SDLK_UP) {
                        if (view_app->Robot.Position.y >= 0) {
                            Mix_PlayChannel(-1,moveSound,-1);
                            personWalkUp(view_app);
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_DOWN) {
                        if (view_app->Robot.Position.y <= 594) {
                            Mix_PlayChannel(-1,moveSound,-1);
                            personWalkDown(view_app);
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_SPACE) {
                        printf("SDLK_SPACE...read the information");
                        printf("display the information");
                    }
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if (ev.button.button == SDL_BUTTON_LEFT) {
                        //check if release & get coordinates
                        point.x = ev.button.x;
                        point.y = ev.button.y;
                        if (ev.window.windowID == SDL_GetWindowID(view_app->Game.window)) {
                            if (SDL_PointInRect(&point, &view_app->Game.Return_b)) {
                                isRunning=SDL_FALSE;
                            }
                        }
                    }
                break;
            }
        }
    }
    //Free Chunk of move
    Mix_FreeChunk(moveSound);
    status =EXIT_SUCCESS;
    return status;
}

int main_controller(View_app *view_app){
    int isRunning = 1;
    int status = EXIT_FAILURE;
    SDL_Event ev;
    SDL_Point point;
    view_app->Actual=Menu;
    //initialise the SDL mixer
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    //load bgm
    Mix_Music *bgm = Mix_LoadMUS("music/bgm.mp3");
    //play BGM in all process
    Mix_PlayMusic(bgm,-1);
    if (init_menu(&view_app->Menu)!=EXIT_SUCCESS){
        fprintf(stderr, "error init_Window : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    //boucle faisant tourner le menu
    while(isRunning==SDL_TRUE){
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_WINDOWEVENT:
                    if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
                        isRunning = SDL_FALSE;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    //check if left click
                    if (ev.button.button == SDL_BUTTON_LEFT) {
                        //check if release & get coordinates
                        point.x = ev.button.x;
                        point.y = ev.button.y;
                        //switch nowhere,return,rules,credits,play
                        switch (view_app->Actual) {
                            case Menu :
                                if (ev.window.windowID == SDL_GetWindowID(view_app->Menu.window)) {
                                    if (SDL_PointInRect(&point, &view_app->Menu.my_buttons[0])) {
                                        //play

                                        free_Windows(&view_app->Menu);

                                        if (init_game(&view_app->Game) != EXIT_SUCCESS) {
                                            fprintf(stderr, "error init_Window : %s", SDL_GetError());
                                            free_Windows(&view_app->Game);
                                            return EXIT_FAILURE;
                                        }
                                        view_app->Actual = Play;

                                        move_robot(view_app);

                                        free_Windows(&view_app->Game);
                                        //executing menu window initialisation and checking it worked
                                        if (init_menu(&view_app->Menu) != EXIT_SUCCESS) {
                                            fprintf(stderr, "error init_Window : %s", SDL_GetError());
                                            free_Windows(&view_app->Menu);
                                            return EXIT_FAILURE;
                                        }
                                        view_app->Actual = Menu;
                                    }
                                    if (SDL_PointInRect(&point, &view_app->Menu.my_buttons[1])) {
                                        //credits
                                        free_Windows(&view_app->Menu);
                                        //executing menu window initialisation and checking it worked
                                        if (init_credits(&view_app->Credits) != EXIT_SUCCESS) {
                                            fprintf(stderr, "error init_Window : %s", SDL_GetError());
                                            free_Windows(&view_app->Credits);
                                            return EXIT_FAILURE;
                                        }
                                        view_app->Actual = Credits;
                                    }
                                    if (SDL_PointInRect(&point, &view_app->Menu.my_buttons[2])) {
                                        //rules
                                        free_Windows(&view_app->Menu);
                                        //executing menu window initialisation and checking it worked
                                        if (init_rules(&view_app->Rules) != EXIT_SUCCESS) {
                                            fprintf(stderr, "error init_Window : %s", SDL_GetError());
                                            free_Windows(&view_app->Credits);
                                            return EXIT_FAILURE;
                                        }
                                        view_app->Actual = Rules;
                                    }
                                    if (SDL_PointInRect(&point, &view_app->Menu.my_buttons[3])) {
                                        //exit
                                        isRunning = 0;
                                        free_Windows(&view_app->Menu);
                                        return status = EXIT_SUCCESS;
                                    }
                                }
                                break;
                            case Rules:
                                if (ev.window.windowID == SDL_GetWindowID(view_app->Rules.window)) {
                                    if (SDL_PointInRect(&point, &view_app->Rules.Return_b)) {
                                        free_Windows(&view_app->Rules);
                                        //executing menu window initialisation and checking it worked
                                        if (init_menu(&view_app->Menu) != EXIT_SUCCESS) {
                                            fprintf(stderr, "error init_Window : %s", SDL_GetError());
                                            free_Windows(&view_app->Menu);
                                            return EXIT_FAILURE;
                                        }
                                        view_app->Actual = Menu;
                                    }

                                }
                                break;
                            case Credits:
                                if (ev.window.windowID == SDL_GetWindowID(view_app->Credits.window)) {
                                    if (SDL_PointInRect(&point, &view_app->Credits.Return_b)) {
                                        free_Windows(&view_app->Credits);
                                        //executing menu window initialisation and checking it worked
                                        if (init_menu(&view_app->Menu) != EXIT_SUCCESS) {
                                            fprintf(stderr, "error init_Window : %s", SDL_GetError());
                                            free_Windows(&view_app->Menu);
                                            return EXIT_FAILURE;
                                        }
                                        view_app->Actual = Menu;
                                    }
                                }
                                break;
                            case Play:
                                break;
                    }
                break;
             }
        }
        status=EXIT_FAILURE;
    }
    }
    //free BGM
    Mix_FreeMusic(bgm);
    //close mixer audio
    Mix_CloseAudio();
    status=EXIT_SUCCESS;
    return status;
}