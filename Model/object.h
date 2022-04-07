//
// Created by eii on 04/04/2022.
//
#include <stdio.h>
#include <stdlib.h>


#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H

typedef struct Object{
    char id;
    int x;
    int y;
    char file_name;
}Object;


typedef struct Door{
    char id;
    int x;
    int y;
    char file_name;
    int access;
}Door;

void createObject(char id, int x, int y, char file_name);
void createDoor(char id, int x, int y, char file_name);
void changeAccess(Door *D);





#endif //MODEL_OBJECT_H
