//
// Created by Margot on 06/04/2022.
//

#include "../Controller/controller.h"



//#include "controller.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include "../View/main_view.h"
//#include "SDL2/SDL.h"
//#include "SDL2/SDL_image.h"
//#include "SDL2/SDL_mixer.h"

VertexList * init_game_engine(){
    // creates room from file
    VertexList * graph = readGraphFile("./Files_descriptors/Graph.txt");
    Room * room1 = readRoomFile("./Files_descriptors/Room1.txt");
    Room * room2 = readRoomFile("./Files_descriptors/Room2.txt");

    associateRoomWithVertexList(graph,room1);
    associateRoomWithVertexList(graph, room2);
/*
    printGraph(graph);
    setOnFirstVertex(graph);
    printRoom(graph->current->R);
    setOnNextVertex(graph);
    printRoom(room2);*/
    return graph;
}

void showRoom (View_app * view_app,Room * room){
    update_room(room->name,room->filename,view_app);
    int obj_id = 0;
    for (int i = 0; i<room->nb_i; i++){
        for (int j= 0; j<room->nb_j; j++){
             if (room->framing[i][j].o != NULL){
                 SDL_Rect temp = {room->framing[i][j].Pos_x+140,room->framing[i][j].Pos_y+140,room->w,room->h};
                 view_app->object[obj_id].position = temp;
                 init_object(view_app,obj_id,room->framing[i][j].o->file_name);
                 obj_id ++;
             }
        }
    }
    if (room->framing[2][0].d != NULL){
        if (strcmp(room->framing[2][0].d->id, "BRB")==0){
            SDL_Rect temp = {room->framing[2][0].Pos_x+140,room->framing[2][0].Pos_y+140,room->w,room->h};
            view_app->object[obj_id].position = temp;
            init_object(view_app,obj_id,room->framing[2][0].d->file_name);
            obj_id ++;
        }
    }
    printf("%d \n", obj_id);
    if (room->framing[2][8].d != NULL){
        if (strcmp(room->framing[2][8].d->id, "BRB")==0){
            SDL_Rect temp = {room->framing[2][8].Pos_x+140,room->framing[2][8].Pos_y+140,room->w,room->h};
            view_app->object[obj_id].position = temp;
            init_object(view_app,obj_id,room->framing[2][8].d->file_name);
            obj_id ++;
        }
    }
}

void initRobot(View_app *view_app,int flag,Personage * p){
    if (flag==1){
        p->y_position=320;
        p->x_position=1190;
        view_app->Robot.Position.y=320+140;
        view_app->Robot.Position.x=1190+140;
    }else if (flag==0){
        p->x_position=0;
        p->y_position=320;
        view_app->Robot.Position.y=320+140;
        view_app->Robot.Position.x=140;
    }
}


int move_robot(View_app *view_app,VertexList * graph) {
    SDL_Point point;

    int isRunning = 1;
    int status = EXIT_FAILURE;
    SDL_Event ev;
    //Load Chunk of move
    Mix_Chunk *moveSound = Mix_LoadWAV("music/Move_Sound.wav");
    if (init_character(view_app) != EXIT_SUCCESS) {
        fprintf (stderr, "failed init character \n");
    }
    Personage * p= CreatePersonage();

    initRobot(view_app,0,p);

    showRoom(view_app,graph->current->R);
    personWalkDown(view_app);
    move_down(p, 10);

    while (isRunning == SDL_TRUE) {
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT:
                    isRunning = SDL_FALSE;
                break;

                case SDL_KEYDOWN:
                    if (ev.key.keysym.sym == SDLK_LEFT) {
                        if (view_app->Robot.Position.x >= 145) {
                            //Play move sound
                            Play_MChunk(moveSound);
                            personWalkLeft(view_app);
                            move_left(p, 10);
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_RIGHT) {
                        if (view_app->Robot.Position.x <= 1330) {
                            //Play move sound
                            Play_MChunk(moveSound);
                            personWalkRight(view_app);
                            move_right(p, 10);
                     }

                    }
                    else if (ev.key.keysym.sym == SDLK_UP) {
                        if (view_app->Robot.Position.y >= 195) {
                            //Play move sound
                            Play_MChunk(moveSound);
                            personWalkUp(view_app);
                            move_up(p, 10);
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_DOWN) {
                        if (view_app->Robot.Position.y <= 605) {
                            //Play move sound
                            Play_MChunk(moveSound);
                            personWalkDown(view_app);
                            move_down(p, 10);
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_SPACE) {
                        int * k = isInteractionPossible(p,graph->current->R);
                        printf("position : (%d;%d) \n",k[0],k[1]);
                        if (k[2]==0){
                            printf("interaction impossible\n");
                        }else if(k[2]==1){
                            printf("interaction with object\n");
                            SolvedEnigma(graph);
                            // quand l'enigme est résolue utiliser cette fonction pour changer les accès
                        }else if(k[2]==2){
                            printf("interaction with door\n");
                            if(create_messageBox(view_app, "Robot" , "You want to pass this door ?","Yes","NO")==0){
                            	printf("pass the door! \n");
                            	}
                            //graph->current->R->framing[k[0]][k[1]].d->access=1;
                            Edge * e = findEdge(graph->current->connect,graph->current->R->framing[k[0]][k[1]].d->id);
                            if(strcmp(e->v_next->label,"win")==0){
                                if(create_messageBox(view_app, "Robot" , "Are you sure you want to do this ? ","Yes","NO")==0){
                            		printf("you win\n");
                            	}
                                //TODO : fenetre GG + retour au menu
                            }else{
                                int j = changeRoom(graph,graph->current->R->framing[k[0]][k[1]].d);
                                if(j==0){
                                    printf("porte fermée\n");
                                }else if (j==1){
                                    int flag;
                                    if(k[1]==0){
                                        flag=1;
                                        graph->current->R->framing[2][8].d->access=1;
                                    }else if(k[1]==8){
                                        flag=0;
                                        graph->current->R->framing[2][0].d->access=1;
                                    }
                                    //free_objects()
                                    showRoom(view_app,graph->current->R);
                                    initRobot(view_app,flag,p);
                                    personWalkRight(view_app);
                                    move_right(p, 10);
                                }
                            }
                        }
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
    Play_Bgm(view_app);
    if (init_menu(&view_app->Menu)!=EXIT_SUCCESS){
        fprintf(stderr, "error init_Window : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    //boucle faisant tourner le menu
    while(isRunning==SDL_TRUE){
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
            case SDL_KEYDOWN:
                    //Click 'm' to pause or replay the bgm IN MENU/RULES/CREDITS.
                    if (ev.key.keysym.sym == SDLK_m) {
                        if (create_messageBox(view_app, "BGM controller" , "Do you want to turn on/off the music ?","YES","NO") == 0){
                            if (Mix_PausedMusic() == 1) {
                                Mix_ResumeMusic();
                            }else{
                                Mix_PauseMusic();
                            }
                        }
                    }
                    //'k' for volume DOWN
                    if (ev.key.keysym.sym == SDLK_k) {
                       Mix_VolumeMusic(Mix_VolumeMusic(-1)-10);
                    }
                    //'l' for volume UP
                    if (ev.key.keysym.sym == SDLK_l) {
                        Mix_VolumeMusic(Mix_VolumeMusic(-1)+10);
                    }
                    break;

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
					 //Click Sound
                                        Play_CChunk();
                                        if (init_game(&view_app->Game) != EXIT_SUCCESS) {
                                            fprintf(stderr, "error init_Window : %s", SDL_GetError());
                                            free_Windows(&view_app->Game);
                                            return EXIT_FAILURE;
                                        }
                                        view_app->Actual = Play;
                                        VertexList * graph = init_game_engine();
                                        printf("ok\n");
                                        setOnFirstVertex(graph);
                                        move_robot(view_app, graph);

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
                                        //Click Sound
                                        Play_CChunk();
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
                                        //Click Sound
                                        Play_CChunk();
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
                                        //Click Sound
                                        Play_CChunk();
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
                                        //Click Sound
                                        Play_CChunk();
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
                                        //Click Sound
                                        Play_CChunk();
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
    //free bgm
    Free_Bgm(view_app);
    status=EXIT_SUCCESS;
    return status;
}


