//
// Created by eii on 10/04/2022.
//

#include "graph.h"
/**
 * EdgeList: liste de lien entre le Vertex et ses successeurs
 */

/*
 * Fonction Gestion de Liste Edge List
 */
void initEdgeList(EdgeList * c){
    // initialise une liste vide
    if (c!=NULL && !isEmptyEdgeList(c)){
        c->current=NULL;
        c->first=c->last;
        c->last=c->first;
    }
}
int isEmptyEdgeList(EdgeList * c){
    return c->first==c->last;
}
void insertFirstEdge(EdgeList *c, char *obj, Vertex * v){
    //create edge
    Edge * e= (Edge *) malloc(sizeof(Edge));
    e->obj_label=obj;
    e->v_next=v;
    if (isEmptyEdgeList(c)){
        //case List is Empty
        e->next_e=c->last;
        c->last=e;
        c->first=e;
    }else{
        // not empty list insert on First
        e->next_e=c->first;
        c->first=e;
    }
}
void insertLastEdge(EdgeList *c, char *obj, Vertex * v){
    //create edge
    Edge * e= (Edge *) malloc(sizeof(Edge));
    e->obj_label=obj;
    e->v_next=v;
    if (isEmptyEdgeList(c)){
        //case List is Empty
        e->next_e=c->last;
        c->last=e;
        c->first=e;
    }else{
        //not empty insert on Last
        e->next_e=c->last;
        c->last->next_e=e;
        c->last=e;
    }
}

/*
 * "travel in the functions"
 */
void setOnFirstEdge(EdgeList *c){
    //met le pointeur "current" sur le premier Edge de la Liste
    if (c!=NULL){
        c->current=c->first;
    }
}
void setOnLastEdge(EdgeList *c){
    //met le pointeur "current" sur le dernier Edge de la Liste
    if (c!=NULL){
        c->current=c->last;
    }
}
void setOnNextEdge(EdgeList *c){
    //met le pointeur "current" sur l'Edge suivant de la Liste
    if (c!=NULL){
        c->current=c->current->next_e;
    }
}

Edge * findEdge(EdgeList *c, char *obj){
    if (c!=NULL && !isEmptyEdgeList(c)){
        setOnFirstEdge(c);
        while(c->current->next_e!=NULL){
            if(c->current->obj_label==obj){
                return c->current;
            }
            setOnNextEdge(c);
        }
    }
    return NULL;
}

/*
 * Print Edge List
 */
void printEdgeList(EdgeList *c){
    if (c!=NULL && !isEmptyEdgeList(c)){
        setOnFirstEdge(c);
        while(c->current->next_e!=NULL){
            printf("   -%s->%s",c->current->obj_label,c->current->v_next->label);
            setOnNextEdge(c);
        }
    }
}

/*
 * Delete Edge
 */
void deleteFirstEdge(EdgeList *c){
    Edge * e = c->first;
    c->first=e->next_e;
    free(e);
}
void deleteEdgeList(EdgeList * c){
    while(!isEmptyEdgeList(c)){
        deleteFirstEdge(c);
    }
    free(c);
}



/**
 * VertexList: liste de vertex
 */




