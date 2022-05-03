//
// Created by eii on 06/04/2022.
//

#ifndef ESCAPEGAMEPROJECT_CONTROLLER_H
#define ESCAPEGAMEPROJECT_CONTROLLER_H
#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_rect.h"
#include "../View/main_view.h"
#include "../Model/model.h"

void move_robot(View_app *view_app);

int main_controller(View_app *view_app);



#endif //ESCAPEGAMEPROJECT_CONTROLLER_H
