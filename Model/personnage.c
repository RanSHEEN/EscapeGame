//
// Created by Kuilong on 2/27/22.
//

#include "personnage.h"

void move_up(Personage p){
    p.y_position = p.y_position + 1;
}
void move_down(Personage p){
    p.y_position = p.y_position - 1;
}
void move_left(Personage p){
    p.x_position = p.x_position + 1;
}
void move_right(Personage p){
    p.x_position = p.x_position - 1;
}
