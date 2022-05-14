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

void free_Windows(Windows * window){
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    SDL_DestroyTexture(window->texture);
}

void free_character(Character * Robot){
    SDL_DestroyTexture(Robot->texture);
}
void free_object (View_Object * object){
    SDL_DestroyTexture(object->texture);
}
void free_view (View_app *view_app){
    if(view_app->Menu.window!=NULL){
        free_Windows(&view_app->Menu);
    }
    else if (view_app->Game.window!=NULL){
        free_Windows(&view_app->Game);
        free_character(&view_app->Robot);
        for (int i=0 ; i<=NB_OF_OBJECTS; i++){
            free_object(&view_app->object[i]);
        }
    }
    else if (view_app->Credits.window!=NULL){
        free_Windows(&view_app->Credits);
    }
    else if (view_app->Rules.window!=NULL){
        free_Windows(&view_app->Rules);
    }
    SDL_Quit();
    IMG_Quit();
}

//Create a message windows with 2 button. and it will return 0/1 after you click button.
//
int create_messageBox(View_app *view_app, char *title, char *message, char *button1, char *button2)
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
    } else {
        return buttonid;
    }
}

int Play_Bgm(View_app * app){
	int status = EXIT_FAILURE;
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
}

int Play_CChunk(){
	int status = EXIT_FAILURE;

    	
    	//Load Chunk of Click
    	Mix_Chunk *clickchunk = Mix_LoadWAV("music/Click_Sound.wav");
    	 if (clickchunk == NULL) {
        	fprintf (stderr, "failed load chunk music \n");
        	return EXIT_FAILURE;
    }
    	Mix_PlayChannel(1,clickchunk,0);
    	SDL_Delay(100);
    	//free chunk of click
    	Mix_FreeChunk(clickchunk);
}

int Play_MChunk(Mix_Chunk *moveSound ){
	int status = EXIT_FAILURE;

    	if (moveSound == NULL) {
        fprintf (stderr, "failed load move Sound \n");
        return EXIT_FAILURE;
    }
    	Mix_PlayChannel(1,moveSound,0);
}

void Free_Bgm(View_app * app){
    	Mix_FreeMusic(app->bgm);
    	Mix_CloseAudio();
}


/* those functions initialise the windows and create their texture/renderer*/
int init_menu(Windows * escape_menu)
{
    int status = EXIT_FAILURE;

    if (0 != SDL_CreateWindowAndRenderer(873,492,SDL_RENDERER_ACCELERATED,&escape_menu->window,&escape_menu->renderer))
    {
        fprintf(stderr, "error SDL_CreateWindowAndRenderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetWindowPosition(escape_menu->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    escape_menu->texture = SDL_CreateTexture(escape_menu->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,873,492);

    if(NULL == escape_menu->texture){
        fprintf(stderr, "error SDL_CreateTexture: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    escape_menu->Type = Menu;
    get_Tittle (escape_menu->Type , escape_menu->title);
    SDL_SetWindowTitle(escape_menu->window, escape_menu->title);

    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    surface = IMG_Load("img/MENU.jpg");
    if (NULL == surface) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(escape_menu->renderer);
        SDL_DestroyWindow(escape_menu->window);
        SDL_DestroyTexture(escape_menu->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(escape_menu->renderer, surface);
    SDL_FreeSurface((SDL_Surface *) surface); /* On libère la surface, on n’en a plus besoin */
    if (NULL == texture) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface: %s", SDL_GetError());
        SDL_FreeSurface(surface); /* On libère la surface, on n’en a plus besoin */
        SDL_DestroyTexture(texture);

        SDL_DestroyRenderer(escape_menu->renderer);
        SDL_DestroyWindow(escape_menu->window);
        SDL_DestroyTexture(escape_menu->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    SDL_SetRenderTarget(escape_menu->renderer,escape_menu->texture);
    SDL_RenderCopy(escape_menu->renderer,texture,NULL,NULL);
    SDL_DestroyTexture(texture);
    SDL_SetRenderTarget(escape_menu->renderer,NULL);
    // link btw window's renderer and texture
    // copy texture onto windows' one
    // free texture
    // renderer doesn't point on anything anymore
    SDL_RenderCopy(escape_menu->renderer,escape_menu->texture,NULL,NULL);
    SDL_RenderPresent(escape_menu->renderer);
    // final copy of windows' texture onto renderer
    // renderer is all pretty and ready :)

    // Display window icon
    SDL_Surface *surfaceIcon = NULL;
    surfaceIcon = IMG_Load("img/exitIcon.png");
    SDL_SetWindowIcon(escape_menu->window,surfaceIcon);
    if (NULL == surfaceIcon) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(escape_menu->renderer);
        SDL_DestroyWindow(escape_menu->window);
        SDL_Quit();
        IMG_Quit();
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

    status = EXIT_SUCCESS;
    return status;
}

int init_credits(Windows * credits_window)
{
    int status = EXIT_FAILURE;
    if (0 != SDL_CreateWindowAndRenderer(1234,694,SDL_RENDERER_ACCELERATED,&credits_window->window,&credits_window->renderer))
    {
        fprintf(stderr, "error SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetWindowPosition(credits_window->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    credits_window->texture = SDL_CreateTexture(credits_window->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,1234,694);

    if(NULL == credits_window->texture){
        fprintf(stderr, "error SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    credits_window->Type = Credits;
    get_Tittle (credits_window->Type , credits_window->title);
    SDL_SetWindowTitle(credits_window->window, credits_window->title);
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load("img/credits.jpg");
    if (NULL == tmp) {
        fprintf(stderr, "Error IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(credits_window->renderer);
        SDL_DestroyWindow(credits_window->window);
        SDL_DestroyTexture(credits_window->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(credits_window->renderer, tmp);
    SDL_FreeSurface(tmp); /* On libère la surface, on n’en a plus besoin */
    if (NULL == texture) {
        fprintf(stderr, "Error SDL_CreateTextureFromSurface : %s", SDL_GetError());
        fprintf(stderr, "Error IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(credits_window->renderer);
        SDL_DestroyWindow(credits_window->window);
        SDL_DestroyTexture(credits_window->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }

    // Display window icon
    SDL_Surface *surfaceIcon = NULL;
    surfaceIcon = IMG_Load("img/exitIcon.png");
    SDL_SetWindowIcon(credits_window->window,surfaceIcon);
    if (NULL == surfaceIcon) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(credits_window->renderer);
        SDL_DestroyWindow(credits_window->window);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetRenderTarget(credits_window->renderer,credits_window->texture);
    // link btw window's renderer and texture
    SDL_RenderCopy(credits_window->renderer,texture,NULL,NULL);
    //copy texture onto windows' one
    SDL_DestroyTexture(texture);
    //free texture
    SDL_SetRenderTarget(credits_window->renderer,NULL);
    //renderer doesn't point on anything anymore
    SDL_RenderCopy(credits_window->renderer,credits_window->texture,NULL,NULL);
    //final copy of windows' texture onto renderer
    SDL_RenderPresent(credits_window->renderer);
    //renderer is all pretty and ready :)

    //initialize the button
    // x=1516 y=4 w=170 h=70
    SDL_Rect return_but = {1128,1,106,51};
    credits_window->Return_b = return_but;

    status = EXIT_SUCCESS;
    return status;
}

int init_rules(Windows * rules_window)
{
    int status = EXIT_FAILURE;
    if (0 != SDL_CreateWindowAndRenderer(1234,694,SDL_RENDERER_ACCELERATED,&rules_window->window,&rules_window->renderer))
    {
        fprintf(stderr, "error SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetWindowPosition(rules_window->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    rules_window->texture = SDL_CreateTexture(rules_window->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,1234,694);

    if(NULL == rules_window->texture){
        fprintf(stderr, "error SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    rules_window->Type = Rules;
    get_Tittle(rules_window->Type , rules_window->title);
    SDL_SetWindowTitle(rules_window->window, rules_window->title);
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load("img/rules.jpg");
    if (NULL == tmp) {
        fprintf(stderr, "Error IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(rules_window->renderer);
        SDL_DestroyWindow(rules_window->window);
        SDL_DestroyTexture(rules_window->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(rules_window->renderer, tmp);
    SDL_FreeSurface(tmp); /* On libère la surface, on n’en a plus besoin */
    if (NULL == texture) {
        fprintf(stderr, "Error SDL_CreateTextureFromSurface : %s", SDL_GetError());
        SDL_DestroyRenderer(rules_window->renderer);
        SDL_DestroyWindow(rules_window->window);
        SDL_DestroyTexture(rules_window->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }

    // Display window icon
    SDL_Surface *surfaceIcon = NULL;
    surfaceIcon = IMG_Load("img/exitIcon.png");
    SDL_SetWindowIcon(rules_window->window,surfaceIcon);
    if (NULL == surfaceIcon) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(rules_window->renderer);
        SDL_DestroyWindow(rules_window->window);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetRenderTarget(rules_window->renderer,rules_window->texture);
    // link btw window's renderer and texture
    SDL_RenderCopy(rules_window->renderer,texture,NULL,NULL);
    //cpoy texture onto windows' one
    SDL_DestroyTexture(texture);
    //free texture
    SDL_SetRenderTarget(rules_window->renderer,NULL);
    //renderer doesn't point on anything anymore
    SDL_RenderCopy(rules_window->renderer,rules_window->texture,NULL,NULL);
    //final copy of windows' texture onto renderer
    SDL_RenderPresent(rules_window->renderer);
    //renderer is all pretty and ready :)

    //initialize the button
    // x=1516 y=4 w=170 h=70
    SDL_Rect return_but = {1128,1,106,51};    rules_window->Return_b = return_but;

    status = EXIT_SUCCESS;
    return status;
}



int init_game(Windows  * game_window){
    int status = EXIT_FAILURE;

    if (0 != SDL_CreateWindowAndRenderer(1546,734,SDL_RENDERER_ACCELERATED,&game_window->window,&game_window->renderer))
    {
        fprintf(stderr, "Error SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetWindowPosition(game_window->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    game_window->texture=SDL_CreateTexture(game_window->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,1546,734);

    if(NULL == game_window->texture){
        fprintf(stderr, "Error SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    game_window->Type = Play;

    get_Tittle (game_window->Type , game_window->title);
    SDL_SetWindowTitle(game_window->window, game_window->title);

    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load("img/background.jpg");
    if (NULL == tmp) {
        fprintf(stderr, "Error IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(game_window->renderer);
        SDL_DestroyWindow(game_window->window);
        SDL_DestroyTexture(game_window->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    texture = SDL_CreateTextureFromSurface(game_window->renderer, tmp);
    SDL_FreeSurface(tmp); /* On libère la surface, on n’en a plus besoin */
    if (NULL == texture) {
        fprintf(stderr, "Error SDL_CreateTextureFromSurface : %s", SDL_GetError());
        SDL_DestroyRenderer(game_window->renderer);
        SDL_DestroyWindow(game_window->window);
        SDL_DestroyTexture(game_window->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }

    // Display window icon
    SDL_Surface *surfaceIcon = NULL;
    surfaceIcon = IMG_Load("img/exitIcon.png");
    SDL_SetWindowIcon(game_window->window,surfaceIcon);
    if (NULL == surfaceIcon) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(game_window->renderer);
        SDL_DestroyWindow(game_window->window);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetRenderTarget(game_window->renderer,game_window->texture);
    SDL_RenderCopy(game_window->renderer,texture,NULL,NULL);
    SDL_DestroyTexture(texture);
    SDL_SetRenderTarget(game_window->renderer,NULL);
    SDL_RenderCopy(game_window->renderer,game_window->texture,NULL,NULL);
    SDL_RenderPresent(game_window->renderer);
    //renderer is all pretty and ready :)

    //initialize the button
    // x=1516 y=4 w=170 h=70

    SDL_Rect return_but = {1400,1,140,60};
    game_window->Return_b = return_but;
    SDL_Rect play = {980,420,140,60};
    game_window->my_buttons[1] = play;
    status = EXIT_SUCCESS;
    return status;
}



int init_character(View_app * app){
    app->Robot.SPEED = 60;

    SDL_Rect temp = {0,320,70,100 };
    app->Robot.Position = temp;
    app->Robot.texture = SDL_CreateTexture(app->Game.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 70, 100);

    if(NULL == app->Robot.texture)
    {
        fprintf(stderr, "Error SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Surface *surface2 = NULL;
    SDL_Texture *texture2 = NULL;

    //need test 
    //texture2 = IMG_LoadTexture(app->Game.renderer, "img/RobotFront1.png");

    surface2 = IMG_Load("img/Robot.png");
    if (NULL == surface2) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    Uint32 color_key = SDL_MapRGB(surface2->format,0,255,0);
    SDL_SetColorKey(surface2,SDL_TRUE,color_key);

    texture2 = SDL_CreateTextureFromSurface(app->Game.renderer, surface2);
    SDL_FreeSurface((SDL_Surface *) surface2);
    if (NULL == texture2) {
        fprintf(stderr, "Error IMG_LoadPNG_RW: %s", SDL_GetError());
        return EXIT_FAILURE;
    }
//    texture2 = SDL_CreateTextureFromSurface(app->Game.renderer, surface2);
//    SDL_FreeSurface((SDL_Surface *) surface2);
//    if (NULL == texture2) {
//        fprintf(stderr, "Error SDL_CreateTextureFromSurface : %s", SDL_GetError());
//        SDL_FreeSurface(surface2); /* On libère la surface, on n’en a plus besoin */
//        SDL_DestroyTexture(texture2);
//        return EXIT_FAILURE;
//    }
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
    SDL_FreeSurface((SDL_Surface *) surface2);

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

void personWalkRight(View_app * app){
//    app->Robot.Position.x += 5;
/* La texture est la cible de rendu, maintenant, on dessine sur la texture. */
//    SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
//    SDL_RenderCopy(app->Game.renderer, app->Robot.texture, NULL, &app->Robot.Position);
//    SDL_RenderPresent(app->Game.renderer);

    SDL_Surface * map = IMG_Load("./img/background.jpg");
    SDL_Surface * img = IMG_Load("./img/RobotRightSide1.png");
    SDL_Surface * img2 = IMG_Load("./img/RobotRightSide2.png");
    if (map == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img2 == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(app->Game.renderer,map);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app->Game.renderer,img);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(app->Game.renderer,img2);

    int i;
    for (i = 0; i<2; i++)
    {
        SDL_RenderClear(app->Game.renderer);
        SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
        SDL_RenderCopy(app->Game.renderer, texture, NULL, &app->Robot.Position);
        SDL_RenderPresent(app->Game.renderer);
        if (app->Robot.Position.x < 1330) {
            app->Robot.Position.x += 2.5;
        }
        SDL_Delay(60);
        SDL_RenderClear(app->Game.renderer);
        SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
        SDL_RenderCopy(app->Game.renderer, texture2, NULL, &app->Robot.Position);
        SDL_RenderPresent(app->Game.renderer);
        SDL_Delay(60);
    }
}

void personWalkLeft(View_app * app) {
//    app->Robot.Position.x -= 5;
    /* La texture est la cible de rendu, maintenant, on dessine sur la texture. */
//    SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
//    SDL_RenderCopy(app->Game.renderer, app->Robot.texture, NULL, &app->Robot.Position);
//    SDL_RenderPresent(app->Game.renderer);

    SDL_Surface * map = IMG_Load("./img/background.jpg");
    SDL_Surface * img = IMG_Load("./img/RobotLeftSide1.png");
    SDL_Surface * img2 = IMG_Load("./img/RobotLeftSide2.png");
    if (map == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img2 == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(app->Game.renderer,map);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app->Game.renderer,img);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(app->Game.renderer,img2);
    int i;
    for (i = 0; i<2; i++)
    {
        SDL_RenderClear(app->Game.renderer);
        SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
        SDL_RenderCopy(app->Game.renderer, texture, NULL, &app->Robot.Position);
        SDL_RenderPresent(app->Game.renderer);
        if (app->Robot.Position.x > 145) {
            app->Robot.Position.x -= 2.5;
        }
        SDL_Delay(60);
        SDL_RenderClear(app->Game.renderer);
        SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
        SDL_RenderCopy(app->Game.renderer, texture2, NULL, &app->Robot.Position);
        SDL_RenderPresent(app->Game.renderer);
        SDL_Delay(60);
    }
}

void personWalkUp(View_app * app){
//    app->Robot.Position.y -= 5;
    /* La texture est la cible de rendu, maintenant, on dessine sur la texture. */
//    SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
//    SDL_RenderCopy(app->Game.renderer, app->Robot.texture, NULL, &app->Robot.Position);
//    SDL_RenderPresent(app->Game.renderer);

    SDL_Surface * map = IMG_Load("./img/background.jpg");
    SDL_Surface * img = IMG_Load("./img/RobotBack1.png");
    SDL_Surface * img2 = IMG_Load("./img/RobotBack2.png");
    if (map == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img2 == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(app->Game.renderer,map);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app->Game.renderer,img);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(app->Game.renderer,img2);

    int i;
    for (i = 0; i<2; i++)
    {
        SDL_RenderClear(app->Game.renderer);
        SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
        SDL_RenderCopy(app->Game.renderer, texture, NULL, &app->Robot.Position);
        SDL_RenderPresent(app->Game.renderer);
        if (app->Robot.Position.y > 195) {
            app->Robot.Position.y -= 2.5;
        }
        SDL_Delay(60);
        SDL_RenderClear(app->Game.renderer);
        SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
        SDL_RenderCopy(app->Game.renderer, texture2, NULL, &app->Robot.Position);
        SDL_RenderPresent(app->Game.renderer);
        SDL_Delay(60);
    }

}

void personWalkDown(View_app * app){
//    app->Robot.Position.y += 5;
    /* La texture est la cible de rendu, maintenant, on dessine sur la texture. */
//    SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
//    SDL_RenderCopy(app->Game.renderer, app->Robot.texture, NULL, &app->Robot.Position);
//    SDL_RenderPresent(app->Game.renderer);

    SDL_Surface * map = IMG_Load("./img/background.jpg");
    SDL_Surface * img = IMG_Load("./img/RobotFront1.png");
    SDL_Surface * img2 = IMG_Load("./img/RobotFront2.png");
    if (map == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    if (img2 == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        SDL_Quit();
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(app->Game.renderer,map);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app->Game.renderer,img);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(app->Game.renderer,img2);

    int i;
    for (i = 0; i<2; i++)
    {
        SDL_RenderClear(app->Game.renderer);
        SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
        SDL_RenderCopy(app->Game.renderer, texture, NULL, &app->Robot.Position);
        SDL_RenderPresent(app->Game.renderer);
        if (app->Robot.Position.y < 605) {
            app->Robot.Position.y += 2.5;
        }
        SDL_Delay(60);
        SDL_RenderClear(app->Game.renderer);
        SDL_RenderCopy(app->Game.renderer, app->Game.texture, NULL, NULL);
        SDL_RenderCopy(app->Game.renderer, texture2, NULL, &app->Robot.Position);
        SDL_RenderPresent(app->Game.renderer);
        SDL_Delay(60);

    }

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
