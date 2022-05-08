//
// Created by Marie on 06/05/22.
//
#include "../Model/model.h"

FILE *openFileRead(char *PATH){
    /**
     * ouvre un fichier en mode lecture
     */
    FILE * pFile=NULL; /* Descripteur du fichier */
    pFile = fopen (PATH,"r");
    if (pFile==NULL) {
        perror (PATH);
    }
    return pFile;
}

void closeFile(FILE *f){
    /**
     * ferme un fichier
     */
    fclose(f);
}

char * readFileLine(FILE *f, char *tampon){
    /**
     * lit une ligne et la stock dans le tableau tampon
     */
    return fgets(tampon,TMAX,f);
}
//read Room file
void readRoomFile(char * PATH){
    /**
     * Ouvre, lit le fichier au chemin PATH, et crée la Room
     * et appelle la fonction read line pour y ajouter des objets/des portes
     */
}
void readRoomFileLine(FILE *f, Room *R){
    /**
     * Lit une ligne du fichier Room (f) et la traite
     * pour ajouter des objets/portes dans la Room (R)
     */
}
//read Graph File
void readGraphFile(char * PATH){
    /**
     * Ouvre, lit le fichier au chemin PATH, et crée le Graph
     * et appelle la fonction read line pour y ajouter des Vertex/liens.
     */
    int cppt=1;
    char * tampon = (char *) malloc(sizeof(char)*TMAX);
    VertexList * g = initGraph();
    FILE * f= openFileRead(PATH);

    rewind(f);
    readFileLine(f,tampon);
    if (strcmp(tampon,"GRAPH")){
        printf("this document does'nt describe a Graph");
    }
    while(readFileLine(f,tampon)!=NULL){
        cppt ++;
        readGraphFileLine(tampon,g);
    }
}
void readGraphFileLine(char * tampon , VertexList * g){
    /**
    * Lit une ligne du fichier Graph (f) et la traite
    * pour ajouter des Vertex/liens dans le Graph (g)
    */
    char * type, vert, status;
    sscanf(tampon,"%s, %s, %s",type,vert,status);
    if(strcmp(type,"Vertex")){
        char * label;
        int e_number;
        sscanf(vert,"label : %s",label);
        sscanf(status, "enigma_number : %d",e_number);
        insertLastVertex(g,label,e_number);
    }else if (strcmp(type,"Edge")){
        char * label_v1, label_v2, obj_label;
        sscanf(vert,"%s->%s",label_v1,label_v2);
        sscanf(status, "obj_label : %s", obj_label);
        Vertex * v1= findVertex(g,label_v1);
        Vertex * v2= findVertex(g,label_v2);
        insertLastEdge(v1->connect,obj_label,v2);
    }else{
        printf("type unknown");
    }
}

