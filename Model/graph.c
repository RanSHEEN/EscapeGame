//
// Created by Marie on 10/04/2022.
//

#include "../Model/model.h"
/**
 * Graph : VertexList représentant la machine d'état du jeu
 */
/**
 * EdgeList: liste de lien entre le Vertex et ses successeurs
 */

/*
 * Fonction Gestion de Liste Edge List
 */
void initEdgeList(EdgeList * c){
    /**
     * initialise l'EdgeList en mettant tous les pointeurs (current, first, last) à NULL
     */
    if (c!=NULL){
        c->current=NULL;
        c->first=NULL;
        c->last=NULL;
    }
}
int isEmptyEdgeList(EdgeList * c){
    /**
     * Nous dit si la liste de liens est vide
     */
    return (c->first==NULL)&&(c->last==NULL);
}
void insertFirstEdge(EdgeList *c, char *obj, Vertex * v){
    /**
     * ajoute un edge en premier dans la liste d'Edge
     */
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
    /**
    * ajoute un edge en dernier dans la liste d'Edge
    */
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
    /**
     * met le pointeur "current" sur le premier Edge de la Liste
     */
    if (c!=NULL){
        c->current=c->first;
    }
}
void setOnLastEdge(EdgeList *c){
    /**
    * met le pointeur "current" sur le dernier Edge de la Liste
    */
    if (c!=NULL){
        c->current=c->last;
    }
}
void setOnNextEdge(EdgeList *c){
    /**
     * met le pointeur "current" sur l'Edge suivant de la Liste
     */
    if (c!=NULL){
        c->current=c->current->next_e;
    }
}

Edge * findEdge(EdgeList *c, char *obj){
    /**
     * cherche dans la liste d'edge et retourne l'edge de label donné en paramètre
     * return NULL si elle n'a pas trouvé l'edge
     */
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
    /**print the EdgeList:
    *    --obj_label--> label
    *    --obj_label--> label
    *    --obj_label--> label
   */
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
    /**
     * supprime le premier Edge de l'EdgeList
     * et en libère la mémoire
     */
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
    /**
     * supprime tous les Edges de l'Edge list et en libère la mémoire
     */
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
VertexList * initGraph(){
    /**
     * crée et alloue un graph (VertexList)
     * ET l'initialise en mettant tous les pointeurs (current, first, last) à NULL
     */
    VertexList * g=(VertexList *) malloc(sizeof(VertexList));
    if (g!=NULL){
        g->current=NULL;
        g->first=NULL;
        g->last=NULL;
    }
    return g;
}
int isEmptyVertexList(VertexList * g){
    /**
     * Nous dit si le graph est vide
     */
    return (g->first==NULL)&&(g->last==NULL);
}
void insertFirstVertex(VertexList * g,char * label,int enigma_number){
    /**
     * ajoute un vertex en premier dans la liste de Vertex
     */
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
    /**
     * ajoute un vertex en dernier dans la liste de Vertex
     */
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
    /**
     * add an edge from the Vretex v1 to the vertex v2
    */
    //Add into v1.connect (EdgeList) using (addLast)
    insertLastEdge(v1->connect, obj_label, v2);
}

/*
 * "travel in the List"
 */
void setOnFirstVertex(VertexList * g){
    /**
     * mets le pointeur Current sur le premier vertex de la liste
     */
    if(g!=NULL){
        g->current=g->first;
    }
}
void setOnLastVertex(VertexList * g){
    /**
     * mets le pointeur Current sur le dernier vertex de la liste
     */
    if(g!=NULL){
        g->current=g->last;
    }
}
void setOnNextVertex(VertexList * g){
    /**
    * mets le pointeur Current sur le vertex suivant de la liste
    */
    if(g!=NULL){
        g->current=g->current->next_v;
    }
}
void setOnPreviousVertex(VertexList *g){
    /**
    * mets le pointeur Current sur le vertex précédent de la liste
    */
    if(g!=NULL){
        g->current=g->current->previous_v;
    }
}
Vertex * findVertex(VertexList * g,char * label){
    /**
     * cherche dans la liste de vertex et retourne le vertex de label donné en paramètre
     * return NULL si elle n'a pas trouvé le Vertex
     */
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
    /**print the graph:
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
 * Delete Vertex
 */
void deleteFirstVertex(VertexList * g){
    /**
     * supprime le premier Vertex de la VertexList
     * et en libère la mémoire
     */
    if (g->first==g->last){
        Vertex *v  = g->first;
        g->first=NULL;
        g->current=NULL;
        g->last=NULL;
        free(v);
    }else{
        Vertex *v  = g->first;
        g->first=v->next_v;
        g->first->previous_v=NULL;
        free(v);
    }
}
void deleteGraph(VertexList * g){
    /**
     * supprime tous les Vertex de la Vertex list et en libère la mémoire
     */
    while(!isEmptyVertexList(g)){
        deleteFirstVertex(g);
    }
    free(g);
}


/**
 * State Change
 * Notre graph s'apparente à uns machine d'état dont les état sont des salles
 * quand on résout les énigmes de l'étape on change d'état
 */

int changeStateAccess(VertexList * g){
    /**
     * Vérifie que le changement de salle peut être autorisée, et si c'est le cas change de salle
     */
    //return 0 si état inchangé, 1 si il change, -1 si erreur
    //Changement d'état autorisé? (enigma nb==solved)
    if(g->current->enigma_solved<g->current->enigma_number){
        return 0;
    }else if(g->current->enigma_solved>g->current->enigma_number){
        return -1;
    }else {
        //plusieurs Edges possibles
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
        //si nouveau Vertex.label = win print "GG"
        return 1;
    }
    return 0;
}

int SolvedEnigma(VertexList * g){
    /**
     * augmente de 1 le nombre d'énigme résolu et appelle la fonction state change pour vérifier si le changement d'état est possible
     */
    g->current->enigma_solved++;
    int c = changeStateAccess(g);
    return c;
}


