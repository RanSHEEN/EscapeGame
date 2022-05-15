//
// Created by Marie on 2/27/22.
//
#include "../Model/model.h"


Personage * CreatePersonage(){
    /**
     * Crée et alloue un personnage
     * en l'initialisant à la position (0;320)
     * (Coins en haut à gauche)
     * la fonction retourne un pointeur vers le personnage
     */
    Personage * p = (Personage *) malloc(sizeof(Personage));
    p->x_position = 0;
    p->y_position = 320;
    return p;
}

void DeletePersonage(Personage * p){
    /**
     * Supprime et libère la mémoir du personnage p
     */
    free(p);
}

void move_up(Personage * p, int n){
    /**
     * Le personnage se déplace vers le haut de n pixels
     * (y_position décroissant)
     */
    p->y_position = p->y_position - n;
    
}
void move_down(Personage * p, int n){
    /**
     * Le personnage se déplace vers le bas de n pixels
     * (y_position croissant)
     */
    p->y_position = p->y_position + n;
    
}
void move_left(Personage * p, int n){
    /**
     * Le personnage se déplace vers la gauche de n pixels
     * (x_position décroissant)
     */
   p->x_position = p->x_position - n;
    
}
void move_right(Personage * p, int n){
    /**
     * Le personnage se déplace vers la droite de n pixels
     * (x_position croissant)
     */
   p->x_position = p->x_position + n;

   
}


