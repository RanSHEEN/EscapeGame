//
// Created by Margot on 06/04/2022.
//

#ifndef ESCAPEGAMEPROJECT_CONTROLLER_H
#define ESCAPEGAMEPROJECT_CONTROLLER_H

#include "../View/main_view.h"
#include "../Model/model.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL.h"

/**
 * \fn VertexList * init_game_engine()
 * \author Marie (et Margot)
 * \details
 * Initialise le graph en lisant les fichiers du niveau
 * @return Pointeur vers le graph du niveau
 */
VertexList * init_game_engine();
/**
 * \fn void showRoom (View_app * view_app,Room * room)
 * \author Margot
 * \details
 * Affiche une salle de jeu et les objet correspondant grâce aux informations reçues du modèle
 * @param view_app paramètre général de la vue
 * @param room Structure du modèle contenant les informations d'une salle (nom du fichier pour le fond, nobre d'objets et leur fichiers respectifs)
 */
void showRoom (View_app * view_app,Room * room);
/**
 * \fn void initRobot(View_app *view_app,int flag, Personage * p)
 * \author Marie
 * \details initialise le personnage robot sur le plan model et sur le plan de la vue
 * @param view_app paramètre général de la vue
 * @param flag un entier permettant de changer la position en focntion du changement de salle
 * @param p structure
 */
void initRobot(View_app *view_app,int flag, Personage * p);
/**
 * \fn int showPopUp (View_app * view_app, char * filename)
 * \author Margot
 * \details affiche une popup pour l'interaction avec un objet
 * @param view_app paramètre général de la vue
 * @param filename le fichier correspondat à l'image de la popup
 * @return 0 si tout ce passe bien à l'ouverture, 1 si elle rencontre un problème
 */
int showPopUp (View_app * view_app, char * filename);
/**
 * \fn
 * int move_robot(View_app *view_app,VertexList * graph)
 * \author
 * Margot
 * \details
 * cette fonction gère la fenêtre de jeu (donc les déplacements du personnage et les interraction avec les objet + bouton retour et fermeture de fenêtre)
 * @param view_app paramètre général de la vue
 * @param graph paramètre général du model, permet de se positionner dans la FSM
 * @return
 */
int move_robot(View_app *view_app,VertexList * graph);
/**
 * \fn
 * int main_controller(View_app *view_app)
 * \author
 * Margot -> structure global et échange entre les fenêtres
 * Ran & Kuilong -> partie musicale
 * \details
 * Controller principal, gère la communication entre la fenêtre menu et toutes les autres ainsi que toutes les actions concernant la musique (volume et on/off)
 * @param view_app
 * @return
 */
int main_controller(View_app *view_app);



#endif //ESCAPEGAMEPROJECT_CONTROLLER_H
