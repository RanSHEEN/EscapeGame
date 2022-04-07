//
// Created by Kuilong on 2/27/22.
//

#ifndef ESCAPEGAMEPROJECT_PERSONNAGE_H
#define ESCAPEGAMEPROJECT_PERSONNAGE_H

<<<<<<< HEAD
=======
#include <stdio.h>
#include <stdlib.h>

>>>>>>> be348f2db29d26e4d6189f5ad4b0ae1d216506a8
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
