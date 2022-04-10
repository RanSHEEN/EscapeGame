//
// Created by Marie on 04/04/2022.
//

#include "object.h"
#include <stdio.h>
#include <stdlib.h>


void createObject(char id, int x, int y, char file_name){
    Object * o= (Object *) malloc(sizeof(Object));
    o->id=id;
    o->file_name=file_name; //nom du png correspondant à l'image
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

/*
* cadrillage model:
* tableau de cases:
 * struct case : position (x,y); objet (=NULL si il n'y a pas d'objet); taille (X,Y)
*/

int getAxesDimension(int a,int b){
    //a=diviseur minimum
    //b=taille que l'on veut diviser en entier
    //return taille divisé (doit être un entier)
    int N=0;
    while(N!=25){
        if (b%a==0){
            printf("%d \n",a);
            return a;
        }
        a=a+1;
        N=N+1;
    }
}

frame ** CreateFraming(){
    int x = getAxesDimension(14,SCREEN_W); //nombre de case en largeur
    int y = getAxesDimension(5,SCREEN_H) ;// nombre de case en hauteur
    frame ** tab=(frame **) malloc(sizeof(frame)*2);
    int w=SCREEN_W/x;//taille d'une case en largeur
    int h=SCREEN_H/y;//taille d'une case en hauteur


    int i,j;
    for(i=0;i<y;i++){
        tab[i]=(frame *) malloc(sizeof(frame)*x);
        for(j=0;j<x;j++){
            tab[i][j].o=NULL;
            tab[i][j].Pos_x=j*w;
            tab[i][j].Pos_y=SCREEN_H-i*h;
            tab[i][j].h=h;
            tab[i][j].w=w;
       }
    }
    return tab;
}

void printFraming(frame ** tab){
    int x = getAxesDimension(14,SCREEN_W); //nombre de case en largeur
    int y = getAxesDimension(5,SCREEN_H) ;// nombre de case en hauteur

    int i,j;
    for(i=0;i<y;i++){
        for(j=0;j<x;j++){
            printf("(%d,%d) ; ",tab[i][j].Pos_x,tab[i][j].Pos_y);
        }
        printf("\n");
    }

}


//delete framing
void deleteFraming(frame ** tab){
    int y = getAxesDimension(5,SCREEN_H) ;// nombre de ligne du tableau
    for(int i = 0 ; i < y ; ++i)
        free((frame *)tab[i]);
    free((frame *)tab);
}
