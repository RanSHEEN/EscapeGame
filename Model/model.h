//
// Created by eii on 07/04/2022.
//

#ifndef ESCAPEGAMEPROJECT_MAIN_MODEL_H
#define ESCAPEGAMEPROJECT_MAIN_MODEL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SCREEN_W 1260
#define SCREEN_H 560
#define TMAX 100
/**
 * object Type enumération
 */
enum obj_type { Button, clue, code };
/**
 * object Type structure
 * an id, his position in the framing, a file name (Path to the .png for the view)
 */
typedef struct {
    char * id;
    int j;
    int i;
    char * file_name;
    enum obj_type type;
}Object;
/**
 * door Type structure
 * an id, his position in the framing, a file name (Path to the .png for the view)
 * la variable access indique si la porte peut être traversée
 */
typedef struct {
    char * id;
    int i;
    int j;
    char * file_name;
    int access;
}Door;
/**
 * Frame structure
 * is a partition of the framing :
 * framing is a table of objects (table ==NULL if no object)
 */
typedef struct {
    int Pos_x; //position height
    int Pos_y; //position Width
    Object * o; //=NULL par defaut
    Door * d;
}frame;
/**
 * struct room describe the room :
 * the height and the width of each frame and their number in line and column of the framing
 * the number of objects present in the room
 * the name of the room
 * the path to the background
 * a pointer to the table framing
 */
typedef struct {
    int h;
    int w; //taille de la case
    int nb_obj;
    int nb_j;
    int nb_i;
    char * name;
    char * filename;
    frame ** framing;
}Room;
/**
 * struct personage describe the character in the model :
 * is position (x,y)
 */
typedef struct {
    int x_position;
    int y_position;
} Personage;

typedef struct Edge Edge;
typedef struct EdgeList EdgeList;
typedef struct Vertex Vertex;
typedef struct VertexList VertexList;
/*
 * definition des objets
 */
/**
    * Crée et alloue un objet
    * @param id : indicateur de l'objet
    * @param j: colonne dans le cadrillage de la Room
     * @param i: ligne dans le cadrillage de la Room
     * @param filename : chemin vers l'image de l'objet
     * @param type : type d'objet
     * @return pointer to the object
     */
Object * createObject(char * id, int x, int y, char * file_name, enum obj_type type);

Door * createDoor(char * id, int x, int y, char * file_name);
void changeAccess(Door *D);
/**
     * libère la mémoire liée à l'objet o
     */
void freeObject(Object *o);
void freeDoor(Door * D);


/*
 * definition Frame
 */

//Create Room
Room * CreateRoom(char * filename, char * name,int nb_obj);
//Create Framing
frame ** CreateFraming(int nb_j, int nb_i, int w, int h);
void printRoom(Room *R);

//delete Framing
void deleteFraming(frame ** tab);
void deleteRoom(Room * R);

// ajouter un objet dans la pièce
void addObject(Room *R, char * id, int i, int j,char *file_name, enum obj_type);
void addDoor(Room *R, char * id, int i, int j,char *file_name);

int * isInteractionPossible(Personage *p, Room * R);
/*
 * definition Personnage
 */


Personage * CreatePersonage();
void DeletePersonage(Personage * p);

void move_up(Personage * p, int n);
void move_down(Personage * p, int n);
void move_left(Personage * p, int n);
void move_right(Personage * p, int n);

/*
 * definition des graph
 * Graph : "Machine d'état" du scénario
 * EdgeList: liste de lien entre le Vertex et ses successeurs
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

/*
 * VertexList: liste de vertex
 */

/*
 * Structures
 */
struct Vertex{
    char * label;
    EdgeList * connect;//vide de base
    Room * R;
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

/*
 * State Change
 * Notre graph s'apparente à uns machine d'état
 * quand on résout les énigmes de l'étape on change d'état
 */

int changeStateAccess(VertexList * g);
int changeRoom(VertexList *g,Door *d);
int SolvedEnigma(VertexList * g);

/*
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
