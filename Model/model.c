//
// Created by Marie on 2/27/22.
//
#include "../Model/model.h"
#include <stdlib.h>

Personage * CreatePersonage(){
    Personage * p = (Personage *) malloc(sizeof(Personage));
    p->x_position = 900;
    p->y_position = 500;
    return p;
}

void DeletePersonage(Personage * p){
    free(p);
}

void move_up(Personage * p, int n){
    p->y_position = p->y_position - n;
}
void move_down(Personage * p, int n){
    p->y_position = p->y_position + n;
}
void move_left(Personage * p, int n){
    p->x_position = p->x_position - n;
}
void move_right(Personage * p, int n){
    p->x_position = p->x_position + n;
}
