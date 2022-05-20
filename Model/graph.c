//
// Created by Marie on 10/04/2022.
//

#include "../Model/model.h"


/*
 * Fonction Gestion de Liste Edge List
 */
void initEdgeList(EdgeList * c){
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
    if (c!=NULL){
        c->current=c->first;
    }
}
void setOnLastEdge(EdgeList *c){
    if (c!=NULL){
        c->current=c->last;
    }
}
void setOnNextEdge(EdgeList *c){
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
        free(e->obj_label);
        free(e);
    }else{
        Edge * e = c->first;
        c->first=e->next_e;
        free(e->obj_label);
        free(e);
    }
}
void deleteEdgeList(EdgeList * c){
    while(!isEmptyEdgeList(c)){
        deleteFirstEdge(c);
    }
    free(c);
}

/*
 * Fonction Gestion de Liste Edge List
 */
VertexList * initGraph(){
    VertexList * g=(VertexList *) malloc(sizeof(VertexList));
    if (g!=NULL){
        g->current=NULL;
        g->first=NULL;
        g->last=NULL;
    }
    return g;
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
        v->previous_v=NULL;
        g->last=v;
        g->first=v;
    }else{
        g->first->previous_v=v;
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
        v->previous_v=NULL;
        g->last=v;
        g->first=v;
    }else{
        v->next_v=NULL;
        v->previous_v=g->last;
        g->last->next_v=v;
        g->last=v;
    }
}
void addLink(Vertex * v1, Vertex * v2, char * obj_label){
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
void setOnPreviousVertex(VertexList *g){
    if(g!=NULL){
        g->current=g->current->previous_v;
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
 * Delete Vertex
 */
void deleteFirstVertex(VertexList * g){
    if (g->first==g->last){
        Vertex *v  = g->first;
        g->first=NULL;
        g->current=NULL;
        g->last=NULL;
        free(v->label);
        free(v);
    }else{
        Vertex *v  = g->first;
        g->first=v->next_v;
        g->first->previous_v=NULL;
        free(v->label);
        free(v);
    }
}
void deleteGraph(VertexList * g){
    while(!isEmptyVertexList(g)){
        deleteFirstVertex(g);
    }
    free(g);
}


/*
 * State Change
 * Notre graph s'apparente à uns machine d'état dont les état sont des salles
 * quand on résout les énigmes de l'étape on change d'état
 */

int changeStateAccess(VertexList * g){
    //return 0 si état inchangé, 1 si il change, -1 si erreur
    //Changement d'état autorisé? (enigma nb==solved)
    if(g->current->enigma_solved<g->current->enigma_number){
        return 0;
    }else if(g->current->enigma_solved>g->current->enigma_number){
        return -1;
    }else {
        if(g->current->R->framing[2][0].d!=NULL){
            g->current->R->framing[2][0].d->access=1;
        }
        if(g->current->R->framing[2][8].d!=NULL){
            g->current->R->framing[2][8].d->access=1;
        }
        return 1;
    }
}

int changeRoom(VertexList *g,Door *d){
    if(d->access==1){
        Edge * e=findEdge(g->current->connect,d->id);
        g->current=e->v_next;
        return 1;
    }
    return 0;
}

int SolvedEnigma(VertexList * g){
    g->current->enigma_solved++;
    int c = changeStateAccess(g);
    return c;
}


void freeStateMachine(VertexList * g){
    if (g!=NULL && !isEmptyVertexList(g)){
        setOnFirstVertex(g);
        while(g->current!=NULL){
            if (g->current->R!=NULL){
                printf("ok1\n");
                deleteRoom(g->current->R);
            }
            printf("ok2\n");
            setOnNextVertex(g);
        }
    }
    deleteGraph(g);
}