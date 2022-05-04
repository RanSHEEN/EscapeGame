//
// Created by Marie on 04/04/2022.
//

#include "model.h"
#include <stdio.h>
#include <stdlib.h>


//Object
Object * createObject(char * id, int j, int i, char * file_name, enum obj_type type){
    Object * o= (Object *) malloc(sizeof(Object));
    o->id=id;
    o->file_name=file_name; //nom du png correspondant à l'image
    o->j = j;
    o->i = i;
    o->type= type;
    return o;
}
void freeObject(Object *o){
    free(o);
}

//Door
Door * createDoor(char * id, int j, int i, char * file_name){
    Door* d= (Door *) malloc(sizeof(Door));
    d->id=id;
    d->file_name=file_name;
    d->j=j;
    d->i=i;
    d->access=0;
    return d;
}
void changeAccess(Door *D){
    if (D->access==0){
        D->access=1;
    }else{
        D->access=0;
    }
}
void freeDoor(Door * D){
    free(D);
}
/*
* cadrillage model:
* tableau de cases:
 * struct case : position (x,y); objet (=NULL si il n'y a pas d'objet); taille (X,Y)
*/

int getDimension(int a,int b){
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
    return b;
}
Room * CreateRoom(char * filename, char * name){
    int nb_j = getDimension(14,SCREEN_W); //nombre de case en largeur
    int nb_i = getDimension(5,SCREEN_H) ;// nombre de case en hauteur
    int w=SCREEN_W/nb_j;//taille d'une case en largeur
    int h=SCREEN_H/nb_i;//taille d'une case en hauteur
    Room * R= (Room *) malloc(sizeof(Room));
    R->nb_j=nb_j;
    R->nb_i=nb_i;
    R->framing= CreateFraming(nb_j,nb_i,w,h);
    R->filename= filename;
    R->name=name;
    R->h=h;
    R->w=w;
    return R;
}
frame ** CreateFraming(int nb_j, int nb_i, int w, int h){
    frame ** tab=(frame **) malloc(sizeof(frame)*2);
    int i,j;
    for(i=0;i<nb_i;i++){
        tab[i]=(frame *) malloc(sizeof(frame)*nb_j);
        for(j=0;j<nb_j;j++){
            tab[i][j].o=NULL;
            tab[i][j].d=NULL;
            tab[i][j].Pos_x=j*w;
            tab[i][j].Pos_y=SCREEN_H-i*h;
       }
    }
    return tab;
}

void printFraming(frame ** tab){
    int x = getDimension(14,SCREEN_W); //nombre de case en largeur
    int y = getDimension(5,SCREEN_H) ;// nombre de case en hauteur

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
    int y = getDimension(5,SCREEN_H) ;// nombre de ligne du tableau
    for(int i = 0 ; i < y ; ++i)
        free((frame *)tab[i]);
    free((frame *)tab);
}
void deleteRoom(Room * R){
    deleteFraming(R->framing);
    free(R);
}

// ajouter un objet dans la pièce
void addObject(Room *R, char * id, int i, int j,char *file_name, enum obj_type type){
    if(R->framing[i][j].d!=NULL){
        fprintf(stderr, "there is a door here");
    }else{
        R->framing[i][j].o= createObject(id,j,i,file_name,type);
    }
}

void addDoor(Room *R, char * id, int i, int j,char *file_name){
    if ((i!=R->nb_i||i!=0)||(j!=R->nb_j||j!=0)) {
        fprintf(stderr, "a door without wall ?");
    }else if (R->framing[i][j].o!=NULL){
        fprintf(stderr, "there is an object here");
    } else{
        R->framing[i][j].d= createDoor(id,j,i,file_name);
    }
}


