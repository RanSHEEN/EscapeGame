//
// Created by eii on 10/04/2022.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

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
    EdgeList * connect;
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
 * Fonction Gestion de Liste Vertex List
 */
//TODO
/*
 * "travel in the List"
 */
//TODO
/*
 * Print Vertex List
 */
//TODO
/*
 * Delete Vertex
 */
//TODO

/**
 * State Change
 * Notre graph s'apparente à uns machine d'état
 * quand on résout les énigmes de l'étape on change d'état
 */

#endif //GRAPH_H
