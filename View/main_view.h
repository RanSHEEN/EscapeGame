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
    SDL_Texture *texture;
    SDL_Rect  Return_b; //return from one window to another
    SDL_Rect  my_buttons[4] ; //navigate btw windows
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
}Menu_windows;


int Launch_view(Menu_windows * escape_menu);
int Game_Window(Menu_windows * game_window);

int init_window(Menu_windows * escape);
/*initializes a menu window and deals with potential errors*/

#endif //PROJET_ESCAPE_MAIN_VIEW_H
