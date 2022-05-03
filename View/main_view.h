//
// Created by Margot on 12/03/2022.
//

#ifndef PROJET_ESCAPE_MAIN_VIEW_H
#define PROJET_ESCAPE_MAIN_VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


enum type {
    Menu,
    Rules,
    Credits,
    Play,
};

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    char title[10];
    enum type Type;
    SDL_Rect  Return_b; //return from one window to menu
    SDL_Rect  my_buttons[4] ; //navigate btw windows in the menu
}Windows;

typedef struct {
    int WALK_PICTURE_NUMBER;
    int SPEED;
    int anim_state;
    SDL_Texture * move_R;
    SDL_Texture * move_L;
    SDL_Texture * move_F;
    SDL_Rect walks_R[8];
    SDL_Rect walks_L[8];
    SDL_Rect walks_F[8];
    SDL_Rect Position ;
} Character;

typedef struct {
   Windows Menu;
   Windows Rules;
   Windows Game;
   Windows Credits;
   Character Robot;
   enum type Actual;
}View_app;


int init_SDL();
void get_Tittle(enum type Type , char* title);
//windows
int init_menu(Windows * escape_menu);
int init_credits(Windows * credits_window);
int init_rules(Windows * rules_window);
int init_game(Windows *game_window);




/* useless
 * struct square {
    SDL_Rect rect;
    Uint32 colour;
};*/

//personnage
int init_character (View_app * app);

void personStatic(View_app * app);
void personWalkRight(View_app * app);
void personWalkLeft(View_app * app);
void personWalkUp(View_app * app);
void personWalkDown(View_app * app);

void free_Windows(Windows * window);
void free_view (View_app *view_app);

int init_View(View_app *view_app);

#endif //PROJET_ESCAPE_MAIN_VIEW_H
