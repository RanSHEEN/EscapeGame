//
// Created by gracesheenxinran on 3/17/22.
//

#ifndef VIEW_GETWINDOW_H
#define VIEW_GETWINDOW_H

#endif //VIEW_GETWINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include "GL/glut.h"

// for installing the glut tool
// we should put glut.h in the package of include folder in mesa/OpenGL


int initialRenderer(SDL_Window *window, SDL_Renderer *ren);
int clearRenderer(SDL_Renderer *ren);
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);