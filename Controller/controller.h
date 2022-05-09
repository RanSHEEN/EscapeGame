//
// Created by Margot on 06/04/2022.
//

#ifndef ESCAPEGAMEPROJECT_CONTROLLER_H
#define ESCAPEGAMEPROJECT_CONTROLLER_H

#include "../View/main_view.h"
#include "../Model/model.h"
/**
 * check le passage possible du personnage en fonction des cases occupées par les objtes (i*room.h -75))
 * @param p
 * @param r
 * @return 0 if can, 1 if can't
 */
int hit_box(Personage * p, Room * r);

int move_robot(View_app *view_app);
int main_controller(View_app *view_app);



#endif //ESCAPEGAMEPROJECT_CONTROLLER_H
