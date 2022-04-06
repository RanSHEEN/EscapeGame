//
// Created by Marie on 04/04/2022.
//

#include "object.h"
#include <stdio.h>
#include <stdlib.h>

void createObject(char id, int x, int y, char file_name){
    Object * o= (Object *) malloc(sizeof(Object));
    o->id=id;
    o->file_name=file_name;
    o->x=x;
    o->y=y;
}

void createDoor(char id, int x, int y, char file_name){
    Door* d= (Door *) malloc(sizeof(Door));
    d->id=id;
    d->file_name=file_name;
    d->x=x;
    d->y=y;
    d->access=0;
}

void changeAccess(Door *D){
    if (D->access==0){
        D->access=1;
    }else{
        D->access=0;
    }
}