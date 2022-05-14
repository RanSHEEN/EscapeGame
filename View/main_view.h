//
// Created by Margot on 12/03/2022.
//

#ifndef PROJET_ESCAPE_MAIN_VIEW_H
#define PROJET_ESCAPE_MAIN_VIEW_H
#define NB_OF_OBJECTS 10
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_mixer.h"



/**
 * enumeration of possible windows types
 */
enum type {
    Menu,
    Rules,
    Credits,
    Play,
};

/**
 * our window structure : a SDL window, renderer and texture,
 * a title (char table)
 * its type based off enum type
 * 5 SDL rectangles for buttons
 */
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    char title[10];
    enum type Type;
    SDL_Rect  Return_b; //return from one window to menu
    SDL_Rect  my_buttons[4] ; //navigate btw windows in the menu
}Windows;

/**
 * character structure : a speed, a rectangle indicating its position, and its specific texture and it's move Sound
 */
typedef struct {
    int SPEED;
    SDL_Texture * texture;
    SDL_Rect Position;
} Character;

/**
 * object structure : and id, a rectangle indicating its position, and its specific texture
 */
typedef struct {
    int id;
    SDL_Rect position;
    SDL_Texture *texture;
}View_Object;

/**
 * View_app structure
 * general view structure
 * 4 windows (Menu,Rules,Game,Credits)
 * a character Robot
 * an object table size of the total nb of objects
 * type Actual, current window type (menu,rules,game,credits)
 * the BGM : bgm
 */
typedef struct {
   Windows Menu;
   Windows Rules;
   Windows Game;
   Windows Credits;
   Character Robot;
   View_Object object [NB_OF_OBJECTS];
   enum type Actual;
   Mix_Music *bgm;
}View_app;


/**
 * int init_SDL video and audio systems
 * deals with all sdl library initializing (here SDL and IMG)
 * @return 0 if no problem during initializing, 1 if goes wrong
 */
int init_SDL();


//windows

/**
 * void get_Tittle
 * Sets a windows title base on its type
 * @param Type
 * @param title
 */
void get_Tittle(enum type Type , char* title);

/**
 * int init_menu
 * initializes and displays the menu window,
 * defines its renderer, texture, window (sized 873x492)
 * and buttons all 170*70 positionned
 * 212x238 : goes to game window
 * 212x345 : goes to credits window
 * 492x238 : goes to rules window
 * 492x345 : exits and closes the project
 * @param app
 * @return 0 if no problem during menu initializing, 1 if goes wrong
 */
 
int init_menu(Windows * escape_menu);
/**
 * int init_credits
 * initializes and displays the credits window,
 * defines its renderer, texture, window (sized 1234x694)
 * and button 106*51 positionned top right corner of the window
 * @param credits_window
 * @return 0 if no problem during credits initializing, 1 if goes wrong
 */
int init_credits(Windows * credits_window);
/**
 * int init_rules
 * initializes and displays the rules window,
 * defines its renderer, texture, window (sized 1234x694)
 * and button 106*51 positionned top right corner of the window
 * @param rules_window
 * @return 0 if no problem during credits initializing, 1 if goes wrong
 */
int init_rules(Windows * rules_window);
/**
 * int init_rules
 * initializes and displays the rules window,
 * defines its renderer, texture, window (sized 1260x700)
 * and buttons all 100*50 positionned top right corner of the window
 * @param game_window
 * @return 0 if no problem during credits initializing, 1 if goes wrong
 */
int init_game(Windows *game_window);


/**
 * used in the controller, this function updates the gaming window background to a defined room
 * @param title
 * @param filename
 * @param view_app
 * @return 0 if no problem during room updating, 1 if goes wrong
 */
int update_room(char * title, char * filename, View_app * view_app);

//personnage
/**
 * int init_character
 * initializes and displays the robot character, defines its position through a SDl rectangle as well as its speed and texture
 * @param app
 * @return 0 if no problem during character initializing, 1 if goes wrong
 */
int init_character (View_app * app);
/**
 * void personWalkRight
 * updates the window with new character position right
 * @param app
 */
void personWalkRight(View_app * app);
/**
 * void personWalkLeft
 * updates the window with new character position left
 * @param app
 */
void personWalkLeft(View_app * app);
/**
 * void personWalkUp
 * updates the window with new character position up
 * @param app
 */
void personWalkUp(View_app * app);
/**
 * void personWalkDown
 * updates the window with new character position down
 * @param app
 */
void personWalkDown(View_app * app);

//objects
/**
 * initializes and displays an object
 * only works in controller after linking object_view and object_model
 * @param app
 * @param nb
 * @param filename
 * @return 0 if went well, 1 if error
 */
int init_object(View_app * app, int nb, char * filename);
/**
 * void free_object
 * frees object (destroy its texture)
 * @param object
 */


//freeing functions

void free_objects (View_Object * object);
/**
 * void free_character
 * frees character (destroy its texture)
 * @param Robot
 */
void free_character(Character * Robot);
/**
 * void free_Windows
 * frees all Windows structure sdl element
 * destroy its renderer, window (as inSDL_Window), and texture
 * @param window
 */
void free_Windows(Windows * window);
/**
 * void free_view
 * smart free of the view elements according to the current open window
 * @param view_app
 */
void free_view (View_app *view_app);

/**
 * int init_View
 * @param view_app
 * @return 0 if no problem during SDL initializing, 1 if goes wrong
 */
int init_View();

int Play_Bgm(View_app * app);
void Free_Bgm(View_app * app);
int Play_MChunk(Mix_Chunk *moveSound);
int Play_CChunk(View_app * app);
int Credits_CChunk(View_app * app);
int Rules_CChunk(View_app * app);
int Exit_CChunk(View_app * app);
//int button_Play_Animation(View_app * app);

/**
 * int create_messageBox
 * @param view_app
 * @param title 
 * @param message
 * @param button1
 * @param button2
 * @return 0 if click button1, 1 if click button2
 */
int create_messageBox(View_app *view_app, char *title, char *message, char *button1, char *button2);


#endif //PROJET_ESCAPE_MAIN_VIEW_H

