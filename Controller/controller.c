//
// Created by Margot on 06/04/2022.
//

#include "../Controller/controller.h"


int move_robot(View_app *view_app) {
    SDL_Point point;

    int isRunning = 1;
    int status = EXIT_FAILURE;
    SDL_Event ev;

    if (init_character(view_app) != EXIT_SUCCESS) {
        fprintf (stderr, "failed init character \n");
        return EXIT_FAILURE;
    }

    Personage * p= CreatePersonage();
    char filename [30];
    strcpy(filename,"./img/coffee.png") ;
    SDL_Rect temp = {420,140,140,140};
    view_app->object[1].position = temp;
    init_object(view_app,1,filename);
    personWalkDown(view_app);
    move_down(p, 5);

    while (isRunning == SDL_TRUE) {
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT:
                    isRunning = SDL_FALSE;
                break;

                case SDL_KEYDOWN:
                    if (ev.key.keysym.sym == SDLK_LEFT) {
                        if (view_app->Robot.Position.x >= 145) {
                            personWalkLeft(view_app);
                            move_left(p, 5);
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_RIGHT) {
                        if (view_app->Robot.Position.x <= 1330) {
                            personWalkRight(view_app);
                            move_right(p, 5);
                     }

                    }
                    else if (ev.key.keysym.sym == SDLK_UP) {
                        if (view_app->Robot.Position.y >= 195) {
                            personWalkUp(view_app);
                            move_up(p, 5);
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_DOWN) {
                        if (view_app->Robot.Position.y <= 605) {
                            personWalkDown(view_app);
                            move_down(p, 5);
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_SPACE) {
                        //is_interact_possible ?+
                        fprintf(stderr,"SDLK_SPACE...read the information");
                        fprintf(stderr,"display the information");
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
    status =EXIT_SUCCESS;
    return status;
}

int main_controller(View_app *view_app){
    int isRunning = 1;
    int status = EXIT_FAILURE;
    SDL_Event ev;
    SDL_Point point;
    view_app->Actual=Menu;
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
    status=EXIT_SUCCESS;
    return status;
}