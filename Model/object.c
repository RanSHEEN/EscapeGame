//
// Created by Marie on 04/04/2022.
//

#include "../Model/model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

Room * CreateRoom(char * filename, char * name){
    int nb_j = 9; //nombre de case en largeur
    int nb_i = 5;// nombre de case en hauteur
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
            tab[i][j].Pos_y=i*h;
       }
    }
    return tab;
}

void printRoom(Room *R){
    printf("%s\n",R->name);
    printf("%s\n",R->filename);

    int i,j;
    for(i=0;i<R->nb_i;i++){
        for(j=0;j<R->nb_j;j++){
            printf("(%d,%d): ",R->framing[i][j].Pos_x,R->framing[i][j].Pos_y);
            if(R->framing[i][j].o!=NULL){
                printf("%s ; ",R->framing[i][j].o->id);
            }else if(R->framing[i][j].d!=NULL){
                printf("%s ; ",R->framing[i][j].d->id);
            }else{
                printf("vide ; ");
            }
        }
        printf("\n");
    }

}


//delete framing
void deleteFraming(frame ** tab){
    int y = 5;// nombre de ligne du tableau
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
        printf( "there is a door here\n");
    }else if(R->framing[i][j].o!=NULL){
        printf("there is an object here\n");
    }else if(i<0||j<0){
        printf( "you are out of the room\n");
    }else{
        R->framing[i][j].o= createObject(id,j,i,file_name,type);
    }
}

void addDoor(Room *R, char * id, int i, int j,char *file_name){
    if (R->framing[i][j].o!=NULL) {
        printf("there is an object here\n");
    }else if(R->framing[i][j].d!=NULL){
        printf( "there is a door here\n");
    }else if (i<0||j<0){
        printf("you are out of the room\n");
    }else if ((i==R->nb_i-1||i==0)||(j==R->nb_j-1||j==0)) {
        R->framing[i][j].d= createDoor(id,j,i,file_name);
    }else{
        printf("a door without wall ?\n");
    }
}


