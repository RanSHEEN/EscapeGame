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
    if (c!=NULL){
        c->current=NULL;
        c->first=NULL;
        c->last=NULL;
    }
}
int isEmptyEdgeList(EdgeList * c){
    return (c->first==NULL)&&(c->last==NULL);
}
void insertFirstEdge(EdgeList *c, char *obj, Vertex * v){
    //create edge
    Edge * e= (Edge *) malloc(sizeof(Edge));
    e->obj_label=obj;
    e->v_next=v;
    if (isEmptyEdgeList(c)){
        //case List is Empty
        e->next_e=NULL;
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
        e->next_e=NULL;
        c->last=e;
        c->first=e;
    }else{
        //not empty insert on Last
        e->next_e=NULL;
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
        while(c->current!=NULL){
            if(strcmp(c->current->obj_label,obj)==0){
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
        while(c->current!=NULL){
            printf("   --%s-->%s\n",c->current->obj_label,c->current->v_next->label);
            setOnNextEdge(c);
        }
    }
}

/*
 * Delete Edge
 */
void deleteFirstEdge(EdgeList *c){
    if (c->first==c->last){
        Edge * e = c->first;
        c->first=NULL;
        c->current=NULL;
        c->last=NULL;
        free(e);
    }else{
        Edge * e = c->first;
        c->first=e->next_e;
        free(e);
    }
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

/*
 * Fonction Gestion de Liste Edge List
 */
void initGraph(VertexList * g){
    if (g!=NULL){
        g->current=NULL;
        g->first=NULL;
        g->last=NULL;
    }
}
int isEmptyVertexList(VertexList * g){
    return (g->first==NULL)&&(g->last==NULL);
}
void insertFirstVertex(VertexList * g,char * label,int enigma_number){
    //Create Vertex
    Vertex * v= (Vertex *) malloc(sizeof(Vertex));
    v->label=label;
    v->enigma_number=enigma_number;
    v->enigma_solved=0;
    //EdgeList vide de base
    v->connect=(EdgeList *)malloc(sizeof(EdgeList));
    initEdgeList(v->connect);
    if (isEmptyVertexList(g)){
        v->next_v=NULL;
        g->last=v;
        g->first=v;
    }else{
        v->next_v=g->first;
        g->first=v;
    }
}
void insertLastVertex(VertexList * g,char * label,int enigma_number){
    //Create Vertex
    Vertex * v= (Vertex *) malloc(sizeof(Vertex));
    v->label=label;
    v->enigma_number=enigma_number;
    v->enigma_solved=0;
    //EdgeList vide de base
    v->connect=(EdgeList *)malloc(sizeof(EdgeList));
    initEdgeList(v->connect);
    if (isEmptyVertexList(g)){
        v->next_v=NULL;
        g->last=v;
        g->first=v;
    }else{
        v->next_v=NULL;
        g->last->next_v=v;
        g->last=v;
    }
}
void addLink(Vertex * v1, Vertex * v2, char * obj_label){
    /*
     * add an edge from v1 to v2
    */
    //Add into v1.connect (EdgeList) using (addLast)
    insertLastEdge(v1->connect, obj_label, v2);
}

/*
 * "travel in the List"
 */
void setOnFirstVertex(VertexList * g){
    if(g!=NULL){
        g->current=g->first;
    }
}
void setOnLastVertex(VertexList * g){
    if(g!=NULL){
        g->current=g->last;
    }
}
void setOnNextVertex(VertexList * g){
    if(g!=NULL){
        g->current=g->current->next_v;
    }
}
Vertex * findVertex(VertexList * g,char * label){
    if (g!=NULL && !isEmptyVertexList(g)){
        setOnFirstVertex(g);
        while(g->current!=NULL){
            if(strcmp(g->current->label,label)==0){
                return g->current;
            }
            setOnNextVertex(g);
        }
    }
    return NULL;
}
/*
 * Print Edge List
 */
void printGraph(VertexList * g){
    /*print the graph:
     * label :
     *    --obj_label--> label
     *    --obj_label--> label
     *    --obj_label--> label
    */
    if (g!=NULL && !isEmptyVertexList(g)){
        setOnFirstVertex(g);
        while(g->current!=NULL){
            printf("%s :\n",g->current->label);
            printEdgeList(g->current->connect);
            setOnNextVertex(g);
        }
    }
}

/*
 * Delete Edge
 */
void deleteFirstVertex(VertexList * g){
    if (g->first==g->last){
        Vertex *v  = g->first;
        g->first=NULL;
        g->current=NULL;
        g->last=NULL;
        free(v);
    }else{
        Vertex *v  = g->first;
        g->first=v->next_v;
        free(v);
    }
}
void deleteGraph(VertexList * g){
    while(!isEmptyVertexList(g)){
        deleteFirstVertex(g);
    }
    free(g);
}


/**
 * State Change
 * Notre graph s'apparente à uns machine d'état
 * quand on résout les énigmes de l'étape on change d'état
 */

int changeState(VertexList * g,Object * o){
    //return 0 si état inchangé, 1 si il change, -1 si erreur
    //Changement d'état autorisé? (enigma nb==solved)
    if(g->current->enigma_solved<g->current->enigma_number){
        return 0;
    }else if(g->current->enigma_solved>g->current->enigma_number){
        return -1;
    }else {
        if (g->current->connect->last==g->current->connect->first){
            // si un seul Edge
            g->current=g->current->connect->first->v_next;
            printf("one\n");
        }else{
            //si plusieurs Edges
            Edge * e=findEdge(g->current->connect,o->id);
            g->current=e->v_next;
            printf("more\n");
        }
        //si nouveau Vertex.label = win print "GG"
        if(strcmp(g->current->label,"win")==0){
            printf("You Win\n");
        }
        return 1;
    }
}

int SolvedEnigma(VertexList * g, Object *o){
    g->current->enigma_solved++;
    return changeState(g,o);
}


