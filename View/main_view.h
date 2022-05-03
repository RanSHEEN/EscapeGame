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
   Windows Menu;
   Windows Rules;
   Windows Game;
   Windows Credits;
   enum type Actual;

}View_app;



int init_SDL();
void get_Tittle(enum type Type , char* title);
int init_window(Windows * window, int SCREEN_WIDTH, int SCREEN_HEIGHT );

int init_menu(Windows * escape_menu);
int init_credits(Windows * credits_window);
int init_rules(Windows * rules_window);
int init_game(Windows *game_window);
int launch_Game(Windows * game_window);

void free_Windows(Windows * window);
void free_view (View_app *view_app);


int init_View(View_app *view_app);


#endif //PROJET_ESCAPE_MAIN_VIEW_H
