//
// Created by Margot on 06/04/2022.
//

#include "../Controller/controller.h"


VertexList * init_game_engine(){
    // creates room from file
    VertexList * graph = readGraphFile("./Files_descriptors/Graph.txt");
    Room * room1 = readRoomFile("./Files_descriptors/Room1.txt");
    Room * room2 = readRoomFile("./Files_descriptors/Room2.txt");

    associateRoomWithVertexList(graph,room1);
    associateRoomWithVertexList(graph, room2);
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

int showPopUp (View_app * view_app, char * filename) {
    SDL_Point point;
    SDL_Event ev;
    int isRunning = SDL_TRUE;
    int status = EXIT_FAILURE;
    char password[50];
    char entry[10];
    int i=0;
    strcpy(password, "WhatElse?");

    display_popup(view_app,filename);
    SDL_StartTextInput();
    while (isRunning == SDL_TRUE) {
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT:
                    isRunning = SDL_FALSE;
                    status = EXIT_SUCCESS;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (ev.button.button == SDL_BUTTON_LEFT) {
                        //check if release & get coordinates
                        point.x = ev.button.x;
                        point.y = ev.button.y;
                        if (ev.window.windowID == SDL_GetWindowID(view_app->Game.window)) {
                            if (SDL_PointInRect(&point, &view_app->popUp.close_popUp)) {
                                //button sound
                                Button_CChunk();
                                isRunning=SDL_FALSE;
                            }
                        }
                    }
                    break;

                case SDL_TEXTINPUT :
                    if (view_app->popUp.popType == Password) {
                        strcpy(&entry[i],ev.text.text);
                        i++;
                        if (i==9){
                            SDL_StopTextInput();
                            char log_password [9];
                            for (int j = 0; j<10; j++){
                                log_password[j]=entry[j];
                            }
                            if (strncmp(log_password,password,9) != 0){
                                //wrong
                                char filename[50];
                                strcpy(filename, "img/passwordWrong.png");
                                display_popup(view_app,filename);
                                status = EXIT_SUCCESS;
                            }else {
                                //right
                                char filename[50];
                                strcpy(filename, "img/passwordRight.png");
                                display_popup(view_app,filename);
                                status =2;
                            }
                        }
                    }
                break;
            }
        }

    }
    free_popup(&view_app->popUp);
    return status;
}

int move_robot(View_app *view_app,VertexList * graph) {
    SDL_Point point;

    int isRunning = 1;
    int status = EXIT_FAILURE;
    SDL_Event ev;
    if (init_character(view_app) != EXIT_SUCCESS) {
        fprintf (stderr, "failed init character \n");
    }
    Personage * p= CreatePersonage();
    initRobot(view_app,0,p);

    showRoom(view_app,graph->current->R);
    personStatic(view_app);

    while (isRunning == SDL_TRUE) {
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT:
                    isRunning = SDL_FALSE;
                    status = EXIT_SUCCESS;
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
                        SDL_StopTextInput();
                        int * k = isInteractionPossible(p,graph->current->R);
                        if (k[2]==0){
                        }else if(k[2]==1){
                            switch (graph->current->R->framing[k[0]][k[1]].o->type){
                                case clue :
                                    view_app->popUp.popType = Clue;
                                    char filename[50];
                                    int i;
                                    if (strcmp(graph->current->R->name, "Room1")==0 ){
                                        i=1;
                                    }else {
                                        i=2;
                                    }
                                    get_filename(view_app->popUp.popType,filename,i);
                                    showPopUp(view_app,filename);
                                    personStatic(view_app);
                                    break;

                                case code :
                                    view_app->popUp.popType = Password;
                                    char filename2[50];
                                    get_filename(view_app->popUp.popType,filename2,0);
                                    if (showPopUp(view_app,filename2) == 2 ){
                                        personStatic(view_app);
                                        SolvedEnigma(graph); // quand l'enigme est résolue, cette fonction change les accès
                                    } else {
                                        personStatic(view_app);
                                    }
                                    break;

                                case Button :

                                    break;
                            }
                        }else if(k[2]==2){
                            if(create_messageBox("Robot" , "You want to pass this door ?","Yes","NO")==0){
                                Edge * e = findEdge(graph->current->connect,graph->current->R->framing[k[0]][k[1]].d->id);
                                if(strcmp(e->v_next->label,"win")==0){
                                    view_app->popUp.popType = Win;
                                    char filename2[50];
                                    get_filename(view_app->popUp.popType,filename2,0);
                                    if(create_messageBox("Robot" , "Are you sure you want to do this ? ","Yes","NO")==0){
                                        showPopUp(view_app,filename2);
                                        isRunning= SDL_FALSE;
                                    }else{
                                        personStatic(view_app);
                                    }

                                }else {
                                    int j = changeRoom(graph, graph->current->R->framing[k[0]][k[1]].d);

                                    if (j == 0) {
                                        create_messageBox("Robot", "This door is closed", "Ah...", "OK...");
                                    } else if (j == 1) {
                                        //free objects
                                        for (int i = 0; i < graph->current->R->nb_obj; i++) {
                                            free_objects(&view_app->object[i]);
                                        }

                                        int flag;
                                        if (k[1] == 0) {
                                            flag = 1;
                                            graph->current->R->framing[2][8].d->access = 1;
                                        } else if (k[1] == 8) {
                                            flag = 0;
                                            graph->current->R->framing[2][0].d->access = 1;
                                        }

                                        showRoom(view_app, graph->current->R);
                                        initRobot(view_app, flag, p);
                                        personStatic(view_app);
                                    }
                                }
                            }
                        }
                        freeTabMemory(k);
                    }
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if (ev.button.button == SDL_BUTTON_LEFT) {
                        //check if release & get coordinates
                        point.x = ev.button.x;
                        point.y = ev.button.y;
                        if (ev.window.windowID == SDL_GetWindowID(view_app->Game.window)) {
                            if (SDL_PointInRect(&point, &view_app->Game.Return_b)) {
                                // button sound
                                Button_CChunk();
                                isRunning=SDL_FALSE;
                                status = EXIT_SUCCESS;
                            }
                        }
                    }
                break;
            }
        }
    }
    DeletePersonage(p);
    freeStateMachine(graph);
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
    Play_Bgm(view_app);
    //boucle faisant tourner le menu
    while(isRunning==SDL_TRUE){
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_KEYDOWN:
                    //Click 'm' to pause or replay the bgm IN MENU/RULES/CREDITS.
                    if (ev.key.keysym.sym == SDLK_m) {
                        if (create_messageBox("BGM controller" , "Do you want to turn on/off the music ?","YES","NO") == 0){
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
                    status = EXIT_SUCCESS;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    //check if left click
                    if (ev.button.button == SDL_BUTTON_LEFT) {
                        //get coordinates
                        point.x = ev.button.x;
                        point.y = ev.button.y;
                        //switch return,rules,credits,play,exit
                        switch (view_app->Actual) {
                            case Menu :
                                if (ev.window.windowID == SDL_GetWindowID(view_app->Menu.window)) {
                                    if (SDL_PointInRect(&point, &view_app->Menu.my_buttons[0])) {
                                        //button sound
                                        Button_CChunk();
                                        //play
                                        free_Windows(&view_app->Menu);

                                        if (init_game(&view_app->Game) != EXIT_SUCCESS) {
                                            fprintf(stderr, "error init_Window : %s", SDL_GetError());
                                            free_Windows(&view_app->Game);
                                            return EXIT_FAILURE;
                                        }
                                        view_app->Actual = Play;
                                        VertexList * graph = init_game_engine();
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
                                        //button sound
                                        Button_CChunk();
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
                                        //button sound
                                        Button_CChunk();
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
                                        //button sound
                                        Button_CChunk();
                                        //exit
                                        isRunning = 0;
                                        status = EXIT_SUCCESS;
                                        free_Windows(&view_app->Menu);
                                    }
                                }
                                break;
                            case Rules:
                                if (ev.window.windowID == SDL_GetWindowID(view_app->Rules.window)) {
                                    if (SDL_PointInRect(&point, &view_app->Rules.Return_b)) {
                                        //button sound
                                        Button_CChunk();
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
                                        //button sound
                                        Button_CChunk();

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