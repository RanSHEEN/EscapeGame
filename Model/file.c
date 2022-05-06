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
}
void readGraphFileLine(FILE *f, VertexList * g){
    /**
    * Lit une ligne du fichier Graph (f) et la traite
    * pour ajouter des Vertex/liens dans le Graph (g)
    */
}

