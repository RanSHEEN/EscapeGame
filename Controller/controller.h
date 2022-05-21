//
// Created by Margot on 06/04/2022.
//

#ifndef ESCAPEGAMEPROJECT_CONTROLLER_H
#define ESCAPEGAMEPROJECT_CONTROLLER_H

#include "../View/main_view.h"
#include "../Model/model.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL.h"

//int hit_box(Personage * p, Room * r);
/**
 * \fn VertexList * init_game_engine()
 * \author Marie
 * \details
 * Initialise le graph en lisant les fichiers du niveau
 * @return Pointeur vers le graph du niveau
 */
VertexList * init_game_engine();

void showRoom (View_app * view_app,Room * room);
void initRobot(View_app *view_app,int flag, Personage * p);
int showPopUp (View_app * view_app, char * filename);
int move_robot(View_app *view_app,VertexList * graph);

int main_controller(View_app *view_app);



#endif //ESCAPEGAMEPROJECT_CONTROLLER_H
