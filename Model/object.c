//
// Created by Marie on 04/04/2022.
//

#include "../Model/model.h"
#include "math.h"

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
    /**
     * Crée et alloue une porte
     * id : indicateur de la porte
     * j: colonne dans le cadrillage de la Room
     * i: ligne dans le cadrillage de la Room
     * filename : chemin vers l'image de la porte
     * access : est par défaut initié à 0 (porte fermée)
     * la fonction retourne un pointeur vers la porte
     */
    Door* d= (Door *) malloc(sizeof(Door));
    d->id=id;
    d->file_name=file_name;
    d->j=j;
    d->i=i;
    d->access=0;
    return d;
}
void changeAccess(Door *D){
    /**
     * passe le paramète access de la porte à 1 (porte ouverte)
     */
    if (D->access==0){
        D->access=1;
    }else{
        D->access=0;
    }
}
void freeDoor(Door * D){
    /**
     * libère la mémoire liée à la porte D
     */
    free(D);
}
/*
* cadrillage model:
* tableau de cases:
 * struct case : position (x,y); objet (=NULL si il n'y a pas d'objet); taille (X,Y)
*/

Room * CreateRoom(char * filename, char * name,int nb_obj){
    /**
     * crée et alloue une Room
     * elle contient le cadrillage qui décrit ce qu'il y a dans la pièce
     * name est le nom de la room
     * filename est le chemin vers l'image de la pièce
     * h est la hauteur d'une case du cadrillage
     * w est la largeur d'une case du cadrillage
     * nb_j est le nombre de case en largeur
     * nb_i est le nombre de case en hauteur
     */
    int nb_j = 9; //nombre de case en largeur
    int nb_i = 4;// nombre de case en hauteur
    int w=SCREEN_W/nb_j;//taille d'une case en largeur
    int h=SCREEN_H/nb_i;//taille d'une case en hauteur
    Room * R= (Room *) malloc(sizeof(Room));
    R->nb_j=nb_j;
    R->nb_i=nb_i;
    R->framing= CreateFraming(nb_j,nb_i,w,h);
    R->filename= filename;
    R->name=name;
    R->nb_obj =nb_obj;
    R->h=h;
    R->w=w;
    return R;
}
frame ** CreateFraming(int nb_j, int nb_i, int w, int h){
    /**
     * Crée le cadrillage framing
     * h est la hauteur d'une case du cadrillage
     * w est la largeur d'une case du cadrillage
     * nb_j est le nombre de case en largeur
     * nb_i est le nombre de case en hauteur
     * l'objet et la porte sont null par défaut
     * Pos_x et Pos_Y sont les coordonées en haut à gauche en pixel d'une case (frame)
     */
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
    /**
     * "print" le cadrillage de la room :
     * Name
     * Filename
     * (x1,y1):door ou object id or vide ; (x2;y1):door ou object id or vide ; ... (xn;y1):door ou object id or vide
     * (x1;y2):door ou object id or vide ; ...
     * ...
     * (x1;ym):door ou object id or vide ; (x2;ym):door ou object id or vide ; ... (xn;ym):door ou object id or vide
     */
    printf("%s\n",R->name);
    printf("%s\n",R->filename);
    printf("%d\n",R->nb_obj);

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
    /**
     * libère les objets
     * et libère la mémoire liée au cadrillage (framing)
     */
    int i,j;
    int y = 4;// nombre de ligne du tableau
    for(i=0;i<y;i++){
        for(j=0;j<9;j++){
            if (tab[i][j].o==NULL){
                freeObject(tab[i][j].o);
            }
            if (tab[i][j].d==NULL){
                freeDoor(tab[i][j].d);
            }
        }
    }
    for(i = 0 ; i < y ; ++i)
        free((frame *)tab[i]);
    free((frame *)tab);
}
void deleteRoom(Room * R){
    /**
     * libère la mémoire liée à la Room
     */
    deleteFraming(R->framing);
    free(R);
}

// ajouter un objet dans la pièce
void addObject(Room *R, char * id, int i, int j,char *file_name, enum obj_type type){
    /**
     * Ajout d'un objet (d'identifiant id, d'obj_type type et d'image file_name) dans la room (R) à la position (i,j)
     * Un objet ne peut pas être créé là où il y a déjà une porte ou un objet
     * Un objet ne peut pas être créé à l'extérieur de la pièce
     */
    if(i==2 && (j==0 || j==8)){
        printf( "there is a door here\n");
    }else if(R->framing[i][j].o!=NULL){
        printf("there is an other object here\n");

    }else{
        R->framing[i][j].o= createObject(id,j,i,file_name,type);
    }
}

void addDoor(Room *R, char * id, int i, int j,char *file_name){
    /**
     * Ajout d'une porte (d'identifiant id et d'image file_name) dans la room (R) à la position (i,j)
     * Une porte ne peut pas être créé qu'en (2,0) ou en (2,8)
     */
    if (i==2 && (j==0 || j==8)) {
        if(R->framing[i][j].d!=NULL) {
            printf("there is already a door here\n");
        }else {
            R->framing[i][j].d= createDoor(id,j,i,file_name);
        }
    }else{
        printf("you can't put a door here\n");
    }
}

int * isInteractionPossible(Personage *p, Room * R){
    /**
     * Vérfie que le personnage peut interragir avec un objet
     * et retourne un poiteur vers un tableau de int:
     * [i ; j ; t]
     * t = 0 si pas d'interraction
     * t= 1 si interraction avec un objet
     * t= 2 si interraction avec une porte
     */
    int * res = (int *)malloc(sizeof(int)*3);

    res[0] = floor(p->y_position/R->h);
    res[1]= floor((p->x_position + 35)/R->w);

    if (R->framing[res[0]][res[1]].o){
        res[2]=1;
    }else if(R->framing[res[0]][res[1]].d){
        res[2]=2;
    }else{
        res[2]=0;
    }

    return res;
}


