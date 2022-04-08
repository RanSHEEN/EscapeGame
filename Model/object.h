//
// Created by eii on 04/04/2022.
//
#include <stdio.h>
#include <stdlib.h>


#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H
#define SCREEN_W 1746
#define SCREEN_H 984

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

/*
* cadrillage model:
* tableau de cases:
 * struct Case : position (x,y); objet (=NULL si il n'y a pas d'objet); taille (X,Y)
*/
typedef struct frame frame;

struct frame{
    int Pos_x; //position height
    int Pos_y; //position Width
    Object * o; //=NULL par defaut
    int h;
    int w; //taille de la case
};


int getDimension(int a,int b);

//Create Framing
frame ** CreateFraming();
void printFraming(frame ** tab);

#endif //MODEL_OBJECT_H
