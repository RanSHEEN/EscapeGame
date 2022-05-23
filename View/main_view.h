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
 * \enum
 * enum type {
    Menu,
    Rules,
    Credits,
    Play,
}
 * \author
 * Margot
 * \details
 * enumeration of possible windows types
 */
enum type {
    Menu,
    Rules,
    Credits,
    Play,
};

/**
 * \enum
 * enum popType{
    Clue,
    Password,
    Win,
}
 * \author
 * Margot
 * \details
 * enumeration of possible pop-up types
 */
enum popType{
    Clue,
    Password,
    Win,
};

/**
 * \struct
 * typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    char title[10];
    enum type Type;
    SDL_Rect  Return_b; //return from one window to menu
    SDL_Rect  my_buttons[4] ; //navigate btw windows in the menu
}Windows
 * \author
 * Margot
 * \details
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

/**\struct
 * typedef struct {
    int SPEED;
    SDL_Texture * texture;
    SDL_Rect Position;
} Character
 * \author
 * Margot
 * \details
 * character structure : a speed, a rectangle indicating its position, and its specific texture and it's move Sound
 * Structure personnage de la vue.
 */
typedef struct {
    int SPEED;
    SDL_Texture * texture;
    SDL_Rect Position;
} Character;

/**
 * \struct
 * typedef struct {
    int id;
    SDL_Rect position;
    SDL_Texture *texture;
}View_Object
 * \author
 * Margot
 * \details
 * Structure objet de la vue.
 */
typedef struct {
    int id;
    SDL_Rect position;
    SDL_Texture *texture;
}View_Object;

/**
 * \struct
 * typedef struct {
    enum popType popType;
    SDL_Rect position;
    SDL_Texture *texture;
    SDL_Rect  close_popUp;
}popUp
 * \author
 * Margot
 * \details
 * popUp structure : a type, a rectangle indicating its position, its specific texture and a button to close it
 * Structure des fenêtres popup ouvertes lors d'une interaction avec un objet.
 */
typedef struct {
    enum popType popType;
    SDL_Rect position;
    SDL_Texture *texture;
    SDL_Rect  close_popUp;
}popUp;

/**
 * \struct
 * Windows Menu;
   Windows Rules;
   Windows Game;
   Windows Credits;
   Character Robot;
   popUp popUp;
   View_Object object [NB_OF_OBJECTS];
   enum type Actual;
   Mix_Music *bgm;
}View_app
 * \author
 * Margot
 * + Ran et Kuilong pour le BGM
 * \details
 * general view structure
 * 4 windows (Menu,Rules,Game,Credits)
 * a character Robot
 * an object table size of the total nb of objects
 * a popup, SDL rectangle acting as a popup window with a button
 * type Actual, current window type (menu,rules,game,credits)
 * the BGM : back ground music
 */
typedef struct {
   Windows Menu;
   Windows Rules;
   Windows Game;
   Windows Credits;
   Character Robot;
   popUp popUp;
   View_Object object [NB_OF_OBJECTS];
   enum type Actual;
   Mix_Music *bgm;
}View_app;


/**
 * \fn int init_SDL()
 * \author
 * Margot
 * \details
 * int init_SDL video and audio systems
 * deals with all sdl library initializing (here SDL and IMG)
 * @return 0 if no problem during initializing, 1 if goes wrong
 */
int init_SDL();



/**
 * \fn void get_Tittle(enum type Type , char* title)
 * \author
 * Margot
 * \details
 * Sets a windows title base on its type
 * @param Type
 * @param title
 */
void get_Tittle(enum type Type , char* title);
/**
 * \fn void get_filename(enum poptype popType , char* title)
 * \author
 * Margot
 * \details
 * gets the background picture's filename corresponding to a popup type
 * @param poptype le type de l'objet lié à la popup : indice, mot de passe ou "gagné"
 * @param filename le fichier à afficher dans la popup
 */
void get_filename (enum popType poptype, char  * filename, int room);
/**
 * \fn int createWindow(int width, int height, Windows * windows, char * filename)
 * \author Margot
 * \details
 * This function creates a SDL window and renderer and opens the image corresponding to the background + the game's icon
 * @param width largeur de fenêtre
 * @param height hauteur de fenêtre
 * @param windows Structure de la vue regoroupant les éléments d'une fenêtre
 * @param filename le fichier du fond de la fenêtre
 * @return 0 if no problem during initializing, 1 if goes wrong
 */
int createWindow(int width, int height, Windows * windows, char * filename);
/**
 * \fn int init_menu(Windows * escape_menu)
 * \author
 * Margot
 * \details
 * initializes and displays the menu window by using the createWindow function
 * and defines its buttons all 170*70 positionned
 * 212x238 : goes to game window
 * 212x345 : goes to credits window
 * 492x238 : goes to rules window
 * 492x345 : exits and closes the project
 * @param escape_menu structure de la vue regoroupant les éléments d'une fenêtre
 * @return 0 if no problem during menu initializing, 1 if goes wrong
 */
int init_menu(Windows * escape_menu);
/**
 * \fn int init_credits(Windows * credits_window)
 * \author
 * Margot
 * \details
 * initializes and displays the credits window,
 * defines its renderer, texture, window (sized 1234x694)
 * and button 106*51 positionned top right corner of the window
 * @param credits_window structure de la vue regoroupant les éléments d'une fenêtre
 * @return 0 if no problem during credits initializing, 1 if goes wrong
 */
int init_credits(Windows * credits_window);
/**
 * \fn int init_menu(Windows * rules_window)
 * \author
 * Margot
 * \details
 * initializes and displays the rules window,
 * defines its renderer, texture, window (sized 1234x694)
 * and button 106*51 positionned top right corner of the window
 * @param rules_window structure de la vue regoroupant les éléments d'une fenêtre
 * @return 0 if no problem during credits initializing, 1 if goes wrong
 */
int init_rules(Windows * rules_window);
/**
 * \fn int init_menu(Windows * game_window)
 * \author
 * Margot
 * \details
 * initializes and displays the rules window,
 * defines its renderer, texture, window (sized 1260x700)
 * and buttons all 100*50 positionned top right corner of the window
 * @param game_window structure de la vue regoroupant les éléments d'une fenêtre
 * @return 0 if no problem during credits initializing, 1 if goes wrong
 */
int init_game(Windows *game_window);


/**
 * \fn int update_room(char * title, char * filename, View_app * view_app)
 * \author
 * Margot
 * \details
 * utilisée dans le contrôleur, cette fonction met à jour le fond de la fenêtre de jeu
 * @param title titre de la fenêtre
 * @param filename le fond de la salle
 * @param view_app structure de la vue
 * @return 0 if no problem during room updating, 1 if goes wrong
 */
int update_room(char * title, char * filename, View_app * view_app);

/**
 * \fn int update_room(char * title, char * filename, View_app * view_app)
 * \author
 * Margot
 * \details
 *  affiche une popup grâce à un rectagle SDL qui se "colle" sur la fenêtre actuelle avec un bouton défini
 * @param view_app structure globale de la vue
 * @param filename l'image de la popup
 * @return  0 if no problem during displaying the popup, 1 if goes wrong
 */
int display_popup(View_app * view_app, char * filename);


//personnage

/**
 * \fn int init_character (View_app * app)
 * \author
 * Margot
 * \details
 * initializes and displays the robot character, defines its position through a SDl rectangle as well as its speed and texture
 * @param app structure globale de la vue
 * @return 0 if no problem during character initializing, 1 if goes wrong
 */
int init_character (View_app * app);
/**
 * \fn void personWalkRight(View_app * app)
 * \author
 * Margot -> fonctionnement de base
 * Ran & Kuilong développement des animation
 * \details
 * updates the window with new character position right
 * @param app structure globale de la vue
 */
void personWalkRight(View_app * app);
/**
 * \fn void personWalkRight(View_app * app)
 * \author
 * Margot -> fonctionnement de base
 * Ran & Kuilong développement des animation
 * \details
 * updates the window with new character position left
 * @param app structure globale de la vue
 */
void personWalkLeft(View_app * app);
/**
 * \fn void personWalkRight(View_app * app)
 * \author
 * Margot -> fonctionnement de base
 * Ran & Kuilong développement des animation
 * \details
 * updates the window with new character position up
 * @param app structure globale de la vue
 */
void personWalkUp(View_app * app);
/**
 * \fn void personWalkRight(View_app * app)
 * \author
 * Margot -> fonctionnement de base
 * Ran & Kuilong développement des animation
 * \details
 * updates the window with new character position +5pxl down
 * @param app structure globale de la vue
 */
void personWalkDown(View_app * app);

/**
 * \fn void personWalkRight(View_app * app)
 * \author
 * Margot
 * \details
 * updates the window with same character position as before its use
 * @param app structure globale de la vue
 */
void personStatic(View_app * app);

//objects

/**
 * \fn int init_object(View_app * app, int nb, char * filename)
 * \author
 * Margot
 * \details
 * initializes and displays an object
 * only works in controller after linking object_view and object_model
 * @param app structure globale de la vue
 * @param nb le rang de l'objet
 * @param filename le fichier correspondat à l'image de l'objet
 * @return 0 if went well, 1 if error
 */
int init_object(View_app * app, int nb, char * filename);



//freeing functions
/**
 * \fn void free_popup (popUp * popUp)
 * \author
 * Margot
 * \details
 * frees popup structure (its texture)
 * @param popUp structure popUP
 */
void free_popup (popUp * popUp);

/**
 * \fn void Free_Bgm(View_app * app)
 * \author
 * Margot
 * \details
 * free music and close mixer audio
 * @param View_app structure globale de la vue
 */
void Free_Bgm(View_app * app);

/**
 * \fn void free_objects (View_Object * object)
 * \author
 * Margot
 * \details
 * frees an object structure by destroying its SDL_texture
 * @param object structure objet
 */
void free_objects (View_Object * object);
/**
 * \fn void free_character(Character * Robot)
 * \author
 * Margot
 * \details
 * frees character (destroy its texture)
 * @param Robot structure du personnage
 */
void free_character(Character * Robot);
/**
 * \fn void free_Windows(Windows * window)
 * \author
 * Margot
 * \details
 * frees all Windows structure sdl element
 * destroy its renderer, window (as inSDL_Window), and texture
 * @param window structure window
 */
void free_Windows(Windows * window);
/**
 * \fn void free_view (View_app *view_app)
 * \author
 * Margot
 * \details
 * free of the view elements according to the current open window
 * @param view_app structure générale de la vue
 */
void free_view (View_app *view_app);

/**
 * \fn int init_View()
 * \author
 * Margot
 * \details
 * calls different initialisation view functions
 * @param view_app general view structure
 * @return 0 if no problem during SDL initializing, 1 if goes wrong
 */
int init_View();


/**
 * \fn int Play_Bgm(View_app * app)
 * \author
 * Ran & Kuilong
 * \details
 * initialise, load and play the background music
 * @param View_app
 * @return 0 if loading bgm successfully, 1 if not
 */
int Play_Bgm(View_app * app);

/**
 * \fn int Play_MChunk(Mix_Chunk *moveSound)
 * \author
 * Ran & Kuiong
 * \details
 * @param moveSound
 * @return
 */
int Play_MChunk(Mix_Chunk *moveSound);

/**
 *
 * \fn int Button_CChunk()
 * \author
 * Ran & Kuilong
 * \details
 * int Play_CChunk
 * do animation and play sounds of 'Play' button
 * @param view_app
 * @return 0 if no problem during SDL initializing, 1 if goes wrong
 */
int Button_CChunk();


/**
 * \fn int create_messageBox(char *title, char *message, char *button1, char *button2)
 * \author
 * Ran & Kuilong
 * \details
 * int create_messageBox
 * @param view_app
 * @param title 
 * @param message
 * @param button1
 * @param button2
 * @return 0 if click button1, 1 if click button2
 */
int create_messageBox(char *title, char *message, char *button1, char *button2);


#endif //PROJET_ESCAPE_MAIN_VIEW_H

