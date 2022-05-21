//created by Margot

//need test
//const int SCREEN_WIDTH = 1746;
//const int SCREEN_HEIGHT = 984;
//const int SPEED = 60;

#include "main_view.h"
#include <stdio.h>
#include <stdlib.h>


/* initializes the SDL library + sub libraries */
int init_SDL(){
    if(0 != SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)){
        fprintf(stderr, "error SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    if(0 == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)){
        fprintf(stderr, "error IMG_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* links window title to its type */
void get_Tittle(enum type Type , char *title){
    switch (Type) {
        case Menu:
            strcpy(title,"Menu Launcher");
            break;
        case Rules:
            strcpy(title,"Rules");
            break;
        case Credits:
            strcpy(title,"Credits");
            break;
        case Play:
            strcpy(title,"Escape This Room !");
            break;
    }
}

void get_filename (enum popType poptype, char  * filename, int room){
    switch (poptype) {
        case Clue :
            if (room ==1){
                strcpy (filename, "img/clue.png");
            }else {
                strcpy (filename, "img/clue2.png");
            }
            break;
        case Password :
            strcpy (filename, "img/password.png");
            break;
        case Win :
            strcpy (filename, "img/win.png");
            break;
    }
}

void free_Windows(Windows * window){
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    SDL_DestroyTexture(window->texture);
}

void free_character(Character * Robot){
    SDL_DestroyTexture(Robot->texture);
}
void free_objects (View_Object * object){
    SDL_DestroyTexture(object->texture);
}

void free_popup (popUp * popUp){
    SDL_DestroyTexture(popUp->texture);
}

void free_view (View_app *view_app){
    if(view_app->Menu.window!=NULL){
        free_Windows(&view_app->Menu);
    }
    else if (view_app->Game.window!=NULL){
        free_Windows(&view_app->Game);
        free_character(&view_app->Robot);
        for (int i=0 ; i<=NB_OF_OBJECTS; i++){
            free_objects(&view_app->object[i]);
        }
        free_popup(&view_app->popUp);
    }
    else if (view_app->Credits.window!=NULL){
        free_Windows(&view_app->Credits);
    }
    else if (view_app->Rules.window!=NULL){
        free_Windows(&view_app->Rules);
    }
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    Free_Bgm(view_app);
}

//Create a message windows with 2 button. and it will return 0/1 after you click button.
//
int create_messageBox(char *title, char *message, char *button1, char *button2)
{
    //Set button of the message box (official example)
    const SDL_MessageBoxButtonData buttons[] = {
            { /* .flags, .buttonid, .text */        0, 0, button1 },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, button2 },
    //      This is for the 3rd button
    //      { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, button3 },
    };
//init SDL_MessageBoxData
    const SDL_MessageBoxData messageboxdata ={
        SDL_MESSAGEBOX_INFORMATION,
                NULL,
                title,
                message,
                2, //number of buttons
                buttons,
                NULL
    };

    //Load the messageBox
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return 1;
    }
    if (buttonid == -1) {
        SDL_Log("no selection");
        return -1;
    } else {
        return buttonid;
    }
}

int Play_Bgm(View_app * app){
	//initialise the SDL mixer
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    //load bgm
    app->bgm = Mix_LoadMUS("music/bgm.mp3");
    if (app->bgm == NULL) {
        fprintf (stderr, "failed load background music \n");
        return EXIT_FAILURE;
    }
    //play BGM
    Mix_PlayMusic(app->bgm,-1);
    return EXIT_SUCCESS;
}

int Button_CChunk(){
    //Load clicking chunk
    Mix_Chunk *clickChunk = Mix_LoadWAV("music/Click_Sound.wav");
    if (clickChunk == NULL) {
        fprintf (stderr, "failed load chunk music \n");
        return EXIT_FAILURE;
    }
    //play sound
    Mix_PlayChannel(1,clickChunk,0);
    SDL_Delay(20);
    //Free chunk
    Mix_FreeChunk(clickChunk);
    return EXIT_SUCCESS;
}


void Free_Bgm(View_app * app){
	//free music
    Mix_FreeMusic(app->bgm);
    //close mixer audio
    Mix_CloseAudio();
}

int createWindow(int width, int height, Windows * windows, char * filename){
    if (0 != SDL_CreateWindowAndRenderer(width,height,SDL_RENDERER_ACCELERATED,&windows->window,&windows->renderer))
    {
        fprintf(stderr, "error SDL_CreateWindowAndRenderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetWindowPosition(windows->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    windows->texture = SDL_CreateTexture(windows->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);

    if(NULL == windows->texture){
        fprintf(stderr, "error SDL_CreateTexture: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    get_Tittle (windows->Type , windows->title);
    SDL_SetWindowTitle(windows->window, windows->title);
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    surface = IMG_Load(filename);
    if (NULL == surface) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(windows->renderer);
        SDL_DestroyWindow(windows->window);
        SDL_DestroyTexture(windows->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(windows->renderer, surface);
    SDL_FreeSurface((SDL_Surface *) surface); /* On libère la surface, on n’en a plus besoin */
    if (NULL == texture) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface: %s", SDL_GetError());
        SDL_FreeSurface(surface); /* On libère la surface, on n’en a plus besoin */
        SDL_DestroyTexture(texture);

        SDL_DestroyRenderer(windows->renderer);
        SDL_DestroyWindow(windows->window);
        SDL_DestroyTexture(windows->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    SDL_SetRenderTarget(windows->renderer,windows->texture);
    SDL_RenderCopy(windows->renderer,texture,NULL,NULL);
    SDL_DestroyTexture(texture);
    SDL_SetRenderTarget(windows->renderer,NULL);
    // link btw window's renderer and texture
    // copy texture onto windows' one
    // free texture
    // renderer doesn't point on anything anymore
    SDL_RenderCopy(windows->renderer,windows->texture,NULL,NULL);
    SDL_RenderPresent(windows->renderer);
    // final copy of windows' texture onto renderer
    // renderer is all pretty and ready :)

    // Display window icon
    SDL_Surface *surfaceIcon = NULL;
    surfaceIcon = IMG_Load("img/exitIcon.png");
    SDL_SetWindowIcon(windows->window,surfaceIcon);
    if (NULL == surfaceIcon) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        SDL_FreeSurface(surfaceIcon);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/* those functions initialise the windows and create their texture/renderer*/
int init_menu(Windows * escape_menu)
{
    int width = 873;
    int height = 492;
    char filename [50];
    strcpy(filename, "img/MENU.jpg");
    escape_menu->Type = Menu;

    if (createWindow(width,height,escape_menu,filename) !=0){
        fprintf(stderr, "Error opening window");
        return EXIT_FAILURE;
    }

    //initialize the buttons
    // x=212 y=238 w=170 h=70
    SDL_Rect Play_but = {212,238,170,70};
    escape_menu->my_buttons [0] = Play_but;

    // x=212 y=345 w=170 h=70
    SDL_Rect Credits_but = {212,345,170,70};
    escape_menu->my_buttons [1] = Credits_but;

    // x=492 y=238 w=170 h=70
    SDL_Rect Rules_but = {492,238,170,70};
    escape_menu->my_buttons [2] = Rules_but;

    // x=492 y=345 w=170 h=70
    SDL_Rect Exit_but = {492,345,170,70};
    escape_menu->my_buttons [3] = Exit_but;
    return EXIT_SUCCESS;
}
int init_credits(Windows * credits_window)
{
    int width = 1234;
    int height = 694;
    char filename [50];
    strcpy(filename, "img/credits.png");
    credits_window->Type = Credits;
    if (createWindow(width,height,credits_window,filename) !=0){
        fprintf(stderr, "Error opening window");
        return EXIT_FAILURE;
    }

    //initialize the button
    // x=1516 y=4 w=170 h=70
    SDL_Rect return_but = {1128,1,106,51};
    credits_window->Return_b = return_but;

    return EXIT_SUCCESS;
}
int init_rules(Windows * rules_window)
{
    int width = 1234;
    int height = 694;
    char filename [50];
    strcpy(filename, "img/rules.jpg");
    rules_window->Type = Rules;
    if (createWindow(width,height,rules_window,filename) !=0){
        fprintf(stderr, "Error opening window");
        return EXIT_FAILURE;
    }

    //initialize the button
    // x=1516 y=4 w=170 h=70
    SDL_Rect return_but = {1128,1,106,51};
    rules_window->Return_b = return_but;

    return EXIT_SUCCESS;
}
int init_game(Windows  * game_window){
    int width = 1546;
    int height = 734;
    char filename [50];
    strcpy(filename, "img/background.jpg");
    game_window->Type = Play;

    if (createWindow(width,height,game_window,filename) !=0){
        fprintf(stderr, "Error opening window");
        return EXIT_FAILURE;
    }

    //initialize the button
    // x=1516 y=4 w=170 h=70

    SDL_Rect return_but = {1400,1,140,60};
    game_window->Return_b = return_but;
    SDL_Rect play = {980,420,140,60};
    game_window->my_buttons[1] = play;
    return EXIT_SUCCESS;
}

int init_character(View_app * app){
    app->Robot.SPEED = 60;

    SDL_Rect temp = {140,460,70,100 };
    app->Robot.Position = temp;
    app->Robot.texture = SDL_CreateTexture(app->Game.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 70, 100);

    if(NULL == app->Robot.texture)
    {
        fprintf(stderr, "Error SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Surface *surface2 = NULL;
    SDL_Texture *texture2 = NULL;

    surface2 = IMG_Load("img/Robot.png");
    if (NULL == surface2) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    Uint32 color_key = SDL_MapRGB(surface2->format,0,255,0);
    SDL_SetColorKey(surface2,SDL_TRUE,color_key);

    texture2 = SDL_CreateTextureFromSurface(app->Game.renderer, surface2);
    SDL_FreeSurface( surface2);
    if (NULL == texture2) {
        fprintf(stderr, "Error IMG_LoadPNG_RW: %s", SDL_GetError());
        SDL_DestroyTexture(texture2);
        return EXIT_FAILURE;
    }

    SDL_SetRenderTarget(app->Game.renderer,app->Robot.texture);
    SDL_RenderCopy(app->Game.renderer,texture2,NULL,NULL);
    SDL_DestroyTexture(texture2);
    SDL_SetTextureBlendMode(app->Robot.texture,SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(app->Game.renderer,NULL);

    SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
    SDL_RenderCopy(app->Game.renderer,app->Robot.texture,NULL,&app->Robot.Position);
    SDL_RenderPresent(app->Game.renderer);
    return EXIT_SUCCESS;
}
int init_object(View_app * app, int nb, char * filename){
    //this function only initializes an object view wise but won't work without it being liked to the model through controller
    app->object[nb].id = nb;
    app->object[nb].texture= SDL_CreateTexture(app->Game.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, app->object[nb].position.w, app->object[nb].position.h);
    if(NULL== app->object[nb].texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Surface *surface2 = NULL;
    SDL_Texture *texture2 = NULL;
    surface2 = IMG_Load(filename);
    if (NULL == surface2) {
        fprintf(stderr,"Erreur IMG_load: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    Uint32 color_key = SDL_MapRGB(surface2->format,0,255,0);
    SDL_SetColorKey(surface2,SDL_TRUE,color_key);
    texture2 = SDL_CreateTextureFromSurface(app->Game.renderer, surface2);
    if (NULL == texture2) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        SDL_FreeSurface(surface2); /* On libère la surface, on n’en a plus besoin */
        SDL_DestroyTexture(texture2);
        return EXIT_FAILURE;
    }

    SDL_SetRenderTarget(app->Game.renderer,app->object[nb].texture);
    SDL_RenderCopy(app->Game.renderer,texture2,NULL,NULL);
    SDL_DestroyTexture(texture2);
    SDL_FreeSurface( surface2);

    SDL_SetTextureBlendMode(app->object[nb].texture,SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(app->Game.renderer,NULL);
    SDL_SetRenderTarget(app->Game.renderer,app->Game.texture);
    SDL_RenderCopy(app->Game.renderer,app->object[nb].texture,NULL,&app->object[nb].position);
    SDL_SetRenderTarget(app->Game.renderer,NULL);
    SDL_RenderCopy(app->Game.renderer,app->Game.texture,NULL,NULL);
    SDL_RenderPresent(app->Game.renderer);
    return EXIT_SUCCESS;
}
int update_room(char * title, char * filename, View_app * view_app){
    SDL_SetWindowTitle(view_app->Game.window, title);
    SDL_Surface *surface_temp = NULL;
    SDL_Texture *texture_temp = NULL;
    surface_temp = IMG_Load(filename);
    if (NULL == surface_temp) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(view_app->Game.renderer);
        SDL_DestroyWindow(view_app->Game.window);
        SDL_DestroyTexture(view_app->Game.texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    texture_temp = SDL_CreateTextureFromSurface(view_app->Game.renderer, surface_temp);
    if (NULL == texture_temp) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        SDL_DestroyRenderer(view_app->Game.renderer);
        SDL_DestroyWindow(view_app->Game.window);
        SDL_DestroyTexture(view_app->Game.texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }

    // Display window icon
    SDL_Surface *surfaceIcon = NULL;
    surfaceIcon = IMG_Load("img/exitIcon.png");
    SDL_SetWindowIcon(view_app->Game.window,surfaceIcon);
    if (NULL == surfaceIcon) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(view_app->Game.renderer);
        SDL_DestroyWindow(view_app->Game.window);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetRenderTarget(view_app->Game.renderer,view_app->Game.texture);
    SDL_RenderCopy(view_app->Game.renderer,texture_temp,NULL,NULL);
    SDL_DestroyTexture(texture_temp);
    SDL_FreeSurface(surface_temp);
    SDL_SetRenderTarget(view_app->Game.renderer,NULL);
    SDL_RenderCopy(view_app->Game.renderer,view_app->Game.texture,NULL,NULL);
    SDL_RenderPresent(view_app->Game.renderer);

    return EXIT_SUCCESS;
}
int display_popup(View_app * app, char * filename){

    SDL_Rect temp = {3*140,140,560,420};
    app->popUp.position = temp;

    app->popUp.texture = SDL_CreateTexture(app->Game.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, app->popUp.position.w, app->popUp.position.h);
    if(NULL== app->popUp.texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Surface *surface2 = NULL;
    SDL_Texture *texture2 = NULL;
    surface2 = IMG_Load(filename);
    if (NULL == surface2) {
        fprintf(stderr,"Erreur IMG_load: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    texture2 = SDL_CreateTextureFromSurface(app->Game.renderer, surface2);
    if (NULL == texture2) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        SDL_FreeSurface(surface2); /* On libère la surface, on n’en a plus besoin */
        SDL_DestroyTexture(texture2);
        return EXIT_FAILURE;
    }

    SDL_SetRenderTarget(app->Game.renderer,app->popUp.texture);
    SDL_RenderCopy(app->Game.renderer,texture2,NULL,NULL);

    SDL_DestroyTexture(texture2);
    SDL_FreeSurface(surface2);

    SDL_SetRenderTarget(app->Game.renderer,NULL);
    SDL_RenderCopy(app->Game.renderer,app->popUp.texture,NULL,&app->popUp.position);
    SDL_RenderPresent(app->Game.renderer);

    SDL_Rect return_but = {828,152,140,60};
    app->popUp.close_popUp = return_but;
    return EXIT_SUCCESS;
}
void personStatic(View_app * app){
    SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
    SDL_RenderCopy(app->Game.renderer, app->Robot.texture, NULL, &app->Robot.Position);
    SDL_RenderPresent(app->Game.renderer);
}

void personWalkRight(View_app * app){
    app->Robot.Position.x+= 5;
    /* La texture est la cible de rendu, maintenant, on dessine sur la texture. */
    SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
    SDL_RenderCopy(app->Game.renderer, app->Robot.texture, NULL, &app->Robot.Position);
    SDL_RenderPresent(app->Game.renderer);
}
void personWalkLeft(View_app * app) {
    app->Robot.Position.x-= 5;
    /* La texture est la cible de rendu, maintenant, on dessine sur la texture. */
    SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
    SDL_RenderCopy(app->Game.renderer, app->Robot.texture, NULL, &app->Robot.Position);
    SDL_RenderPresent(app->Game.renderer);
}
void personWalkUp(View_app * app){
    app->Robot.Position.y-= 5;
    /* La texture est la cible de rendu, maintenant, on dessine sur la texture. */
    SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
    SDL_RenderCopy(app->Game.renderer, app->Robot.texture, NULL, &app->Robot.Position);
    SDL_RenderPresent(app->Game.renderer);
}
void personWalkDown(View_app * app){
    app->Robot.Position.y+= 5;
    /* La texture est la cible de rendu, maintenant, on dessine sur la texture. */
    SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
    SDL_RenderCopy(app->Game.renderer, app->Robot.texture, NULL, &app->Robot.Position);
    SDL_RenderPresent(app->Game.renderer);
}

int init_View(){
    //executing SDL initialisation and checking it worked
    if (init_SDL() != EXIT_SUCCESS) {
        fprintf(stderr, "error init_Window : %s", SDL_GetError());
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
