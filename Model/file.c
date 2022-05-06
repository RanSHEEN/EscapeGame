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

