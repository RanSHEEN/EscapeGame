//
// Created by eii on 07/04/2022.
//

#ifndef ESCAPEGAMEPROJECT_MAIN_MODEL_H
#define ESCAPEGAMEPROJECT_MAIN_MODEL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SCREEN_W 1851
#define SCREEN_H 1040

/**
 * definition des objets
 */
typedef struct Object{
    char * id;
    int x;
    int y;
    char * file_name;
}Object;


typedef struct Door{
    char * id;
    int x;
    int y;
    char * file_name;
    int access;
}Door;

Object * createObject(char * id, int x, int y, char * file_name);
Door * createDoor(char * id, int x, int y, char * file_name);
void changeAccess(Door *D);

void freeObject(Object *o);
void freeDoor(Door * D);


/***
 * definition Frame
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

//delete Framing
void deleteFraming(frame ** tab);


/**
 * definition Personnage
 */
typedef struct Personage {
    int x_position;
    int y_position;
    //Face begin_face;
}Personage;

/* face of the personage in which direction */
//typedef enum {UP,DOWN,LEFT,RIGHT} Face;

Personage * CreatePersonage();
void DeletePersonage(Personage * p);

void move_up(Personage * p);
void move_down(Personage * p);
void move_left(Personage * p);
void move_right(Personage * p);

/**
 * definition des graph
 */
/**
 * Graph : "Machine d'état" du scénario
 */

//definitions des structures

typedef struct Edge Edge;
typedef struct EdgeList EdgeList;

typedef struct Vertex Vertex;
typedef struct VertexList VertexList;

/**
 * EdgeList: liste de lien entre le Vertex et ses successeurs
 */
/*
 * Structures
 */
struct Edge{
    char * obj_label;
    Vertex *v_next;
    struct Edge *next_e;
};

struct EdgeList{
    Edge *first;
    Edge *current;
    Edge *last;
};

/*
 * Fonction Gestion de Liste Edge List
 */
void initEdgeList(EdgeList * c);
int isEmptyEdgeList(EdgeList * c);
void insertFirstEdge(EdgeList *c, char *obj, Vertex * v);
void insertLastEdge(EdgeList *c, char *obj, Vertex * v);

/*
 * "travel in the List"
 */
void setOnFirstEdge(EdgeList *c);
void setOnLastEdge(EdgeList *c);
void setOnNextEdge(EdgeList *c);
Edge * findEdge(EdgeList *c, char *obj);
/*
 * Print Edge List
 */
void printEdgeList(EdgeList *c);

/*
 * Delete Edge
 */
void deleteFirstEdge(EdgeList *c);
void deleteEdgeList(EdgeList * c);



/**
 * VertexList: liste de vertex
 */

/*
 * Structures
 */
struct Vertex{
    char * label;
    EdgeList * connect;//vide de base
    int enigma_number;
    Vertex * next_v;
    int enigma_solved; //à 0 de base
};

struct VertexList{
    Vertex *first;
    Vertex *current;
    Vertex *last;
};

/*
 * Fonction Gestion de Liste Edge List
 */
void initGraph(VertexList * g);
int isEmptyVertexList(VertexList * g);
void insertFirstVertex(VertexList * g,char * label,int enigma_number);
void insertLastVertex(VertexList * g,char * label,int enigma_number);
void addLink(Vertex * v1, Vertex * v2, char * obj_label);

/*
 * "travel in the List"
 */
void setOnFirstVertex(VertexList * g);
void setOnLastVertex(VertexList * g);
void setOnNextVertex(VertexList * g);
Vertex * findVertex(VertexList * g,char * label);
/*
 * Print Edge List
 */
void printGraph(VertexList * g);

/*
 * Delete Edge
 */
void deleteFirstVertex(VertexList * g);
void deleteGraph(VertexList * g);

/**
 * State Change
 * Notre graph s'apparente à uns machine d'état
 * quand on résout les énigmes de l'étape on change d'état
 */

int changeState(VertexList * g,Object * o);
int SolvedEnigma(VertexList * g, Object *o);


#endif //ESCAPEGAMEPROJECT_MAIN_MODEL_H

