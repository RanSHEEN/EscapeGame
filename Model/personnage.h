//
// Created by Kuilong on 2/27/22.
//

#ifndef ESCAPEGAMEPROJECT_PERSONNAGE_H
#define ESCAPEGAMEPROJECT_PERSONNAGE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Personage {
    int x_position;
    int y_position;
    //Face begin_face;
}Personage;

/* face of the personage in which direction */
//typedef enum {UP,DOWN,LEFT,RIGHT} Face;

void move_up(Personage p);
void move_down(Personage p);
void move_left(Personage p);
void move_right(Personage p);

#endif //ESCAPEGAMEPROJECT_PERSONNAGE_H
