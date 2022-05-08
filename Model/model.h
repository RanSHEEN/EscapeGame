//
// Created by eii on 07/04/2022.
//

#ifndef ESCAPEGAMEPROJECT_MAIN_MODEL_H
#define ESCAPEGAMEPROJECT_MAIN_MODEL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SCREEN_W 1260
#define SCREEN_H 700
#define TMAX 100

enum obj_type { Button, to_look, code };

typedef struct {
    char * id;
    int j;
    int i;
    char * file_name;
    enum obj_type type;
}Object;
typedef struct {
    char * id;
    int i;
    int j;
    char * file_name;
    int access;
}Door;

typedef struct {
    int Pos_x; //position height
    int Pos_y; //position Width
    Object * o; //=NULL par defaut
    Door * d;
}frame;
typedef struct {
    int h;
    int w; //taille de la case
    int nb_j;
    int nb_i;
    char * name;
    char * filename;
    frame ** framing;
}Room;

typedef struct {
    int x_position;
    int y_position;
} Personage;

typedef struct Edge Edge;
typedef struct EdgeList EdgeList;
typedef struct Vertex Vertex;
typedef struct VertexList VertexList;
/**
 * definition des objets
 */

Object * createObject(char * id, int x, int y, char * file_name, enum obj_type type);
Door * createDoor(char * id, int x, int y, char * file_name);
void changeAccess(Door *D);

void freeObject(Object *o);
void freeDoor(Door * D);


/***
 * definition Frame
 */

//Create Room
Room * CreateRoom();
//Create Framing
frame ** CreateFraming();
void printRoom(Room *R);

//delete Framing
void deleteFraming(frame ** tab);
void deleteRoom(Room * R);

// ajouter un objet dans la pièce
void addObject(Room *R, char * id, int i, int j,char *file_name, enum obj_type);
void addDoor(Room *R, char * id, int i, int j,char *file_name);
/**
 * definition Personnage
 */


Personage * CreatePersonage();
void DeletePersonage(Personage * p);

void move_up(Personage * p, int n);
void move_down(Personage * p, int n);
void move_left(Personage * p, int n);
void move_right(Personage * p, int n);

/**
 * definition des graph
 * Graph : "Machine d'état" du scénario
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
    Room *R;
    int enigma_number;
    Vertex * previous_v;
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
VertexList * initGraph();
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
void setOnPreviousVertex(VertexList *g);
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

/**
 * Lecture de fichiers
 */
//open close
FILE *openFileRead(char *nom);
void closeFile(FILE *f);
//read line
char * readFileLine(FILE *f, char *tampon);
//read Room file
Room * readRoomFile(char * PATH);
void readRoomFileLine(char * tampon,Room *R);
//read Graph File
VertexList * readGraphFile(char * PATH);
void readGraphFileLine(char * tampon, VertexList * g);

void associateRoomWithVertexList(VertexList *g,Room *R);
#endif //ESCAPEGAMEPROJECT_MAIN_MODEL_H
