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
VertexList * readGraphFile(char * PATH){
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
    if (strcmp(tampon,"GRAPH\n")!=0){
        printf("this document does not describe a Graph \n");
        return NULL;
    }
    while(readFileLine(f,tampon)!=NULL){
        cppt ++;
        readGraphFileLine(tampon,g);
    }
    closeFile(f);
    free(tampon);
    printf("%d\n",cppt);
    return g;
}
void readGraphFileLine(char * tampon , VertexList * g){
    /**
    * Lit une ligne du fichier Graph (f) et la traite
    * pour ajouter des Vertex/liens dans le Graph (g)
    */
    char * type = (char *) malloc(sizeof(char)*20);

    sscanf(tampon,"%s -\n",type);
    //printf("%s\n",type);

    if(strcmp(type,"Vertex")==0){
        char * label = (char *) malloc(sizeof(char)*20);
        int e_number;

        sscanf(tampon,"Vertex - label:%s - enigma_number:%d\n",label,&e_number);

        insertLastVertex(g,label,e_number);

    }else if (strcmp(type,"Edge")==0){
        char * label_v1 = (char *) malloc(sizeof(char)*20);
        char * label_v2 = (char *) malloc(sizeof(char)*20);
        char * obj_label = (char *) malloc(sizeof(char)*20);

        sscanf(tampon,"Edge - %s - %s - obj_label:%s\n",label_v1,label_v2,obj_label);

        Vertex * v1= findVertex(g,label_v1);
        Vertex * v2= findVertex(g,label_v2);

        insertLastEdge(v1->connect,obj_label,v2);

    }else{
        printf("type unknown\n");
    }
    free(type);
}

