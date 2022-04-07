//
// Created by Margot on 12/03/2022.
//

#ifndef PROJET_ESCAPE_MAIN_VIEW_H
#define PROJET_ESCAPE_MAIN_VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

enum Window {
    Menu,
    Rules,
    Credits,
    Play,
};

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *Menu;
    SDL_Rect  Return_b; //return from one window to another
    SDL_Rect  my_buttons[4] ; //navigate btw windows
}Menu_windows;


int Launch_view();

int init_menu(Menu_windows * escape);
/*initializes a menu window and deals with potential errors*/
int free_menu (Menu_windows * escape);
/*deletes menu window, frees memory and deals with potential errors*/
int launch_menu();


int init_button();
/*initializes a button and deals with potential errors*/
int define_button();

#endif //PROJET_ESCAPE_MAIN_VIEW_H
