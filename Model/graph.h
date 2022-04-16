//
// Created by eii on 10/04/2022.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#endif //GRAPH_H
