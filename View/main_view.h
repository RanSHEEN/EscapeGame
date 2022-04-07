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
    Credits
};
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *Menu;
    SDL_Rect  Return_b;
    SDL_Rect  my_button[4] ;
}Menu_windows;

int init_menu(Menu_windows * escape);
/*initializes a menu window and deals with potential errors*/
int free_menu (Menu_windows * escape);
/*deletes menu window, frees memory and deals with potential errors*/


#endif //PROJET_ESCAPE_MAIN_VIEW_H
