#include "main_view.h"


/* initializes the SDL library +sub libraries */
int init_SDL(){
    if(0 != SDL_Init(SDL_INIT_VIDEO)){
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
void get_Tittle(enum type Type , char* title){
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

void free_view (View_app *view_app){
    if(view_app->Menu.window!=NULL){
        free_Windows(&view_app->Menu);
    }
    else if (view_app->Game.window!=NULL){
        free_Windows(&view_app->Game);
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


/* those functions initialise the windows and create their texture/renderer*/
int init_menu(Windows * escape_menu)
{
    int status = EXIT_FAILURE;

    if (0 != SDL_CreateWindowAndRenderer(873,492,SDL_RENDERER_ACCELERATED,&escape_menu->window,&escape_menu->renderer))
    {
        fprintf(stderr, "error SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetWindowPosition(escape_menu->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    escape_menu->texture=SDL_CreateTexture(escape_menu->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,873,492);

    if(NULL== escape_menu->texture){
        fprintf(stderr, "error SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    escape_menu->Type=Menu;
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
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
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
    //copy texture onto windows' one
    // free texture
    // renderer doesn't point on anything anymore
    SDL_RenderCopy(escape_menu->renderer,escape_menu->texture,NULL,NULL);
    SDL_RenderPresent(escape_menu->renderer);
    // final copy of windows' texture onto renderer
    // renderer is all pretty and ready :)

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
    if (0 != SDL_CreateWindowAndRenderer(1851,1040,SDL_RENDERER_ACCELERATED,&credits_window->window,&credits_window->renderer))
    {
        fprintf(stderr, "error SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetWindowPosition(credits_window->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    credits_window->texture=SDL_CreateTexture(credits_window->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,1851,1040);

    if(NULL== credits_window->texture){
        fprintf(stderr, "error SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    credits_window->Type=Credits;
    get_Tittle (credits_window->Type , credits_window->title);
    SDL_SetWindowTitle(credits_window->window, credits_window->title);
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load("img/credits.jpg");
    if (NULL == tmp) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
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
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
        SDL_DestroyRenderer(credits_window->renderer);
        SDL_DestroyWindow(credits_window->window);
        SDL_DestroyTexture(credits_window->texture);
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
    SDL_Rect return_but = {1690,1,160,76};
    credits_window->Return_b = return_but;

    status = EXIT_SUCCESS;
    return status;
}
int init_rules(Windows * rules_window)
{
    int status = EXIT_FAILURE;
    if (0 != SDL_CreateWindowAndRenderer(1851,1040,SDL_RENDERER_ACCELERATED,&rules_window->window,&rules_window->renderer))
    {
        fprintf(stderr, "error SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetWindowPosition(rules_window->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    rules_window->texture=SDL_CreateTexture(rules_window->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,1851,1040);

    if(NULL== rules_window->texture){
        fprintf(stderr, "error SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    rules_window->Type=Rules;
    get_Tittle (rules_window->Type , rules_window->title);
    SDL_SetWindowTitle(rules_window->window, rules_window->title);
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load("img/rules.jpg");
    if (NULL == tmp) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
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
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        SDL_DestroyRenderer(rules_window->renderer);
        SDL_DestroyWindow(rules_window->window);
        SDL_DestroyTexture(rules_window->texture);
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
    SDL_Rect return_but = {1690,1,160,76};
    rules_window->Return_b = return_but;


    status = EXIT_SUCCESS;
    return status;
}
int init_game(Windows  * game_window){

    int status = EXIT_FAILURE;

    if (0 != SDL_CreateWindowAndRenderer(1851,1040,SDL_RENDERER_ACCELERATED,&game_window->window,&game_window->renderer))
    {
        fprintf(stderr, "error SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetWindowPosition(game_window->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    game_window->texture=SDL_CreateTexture(game_window->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,1851,1040);

    if(NULL== game_window->texture){
        fprintf(stderr, "error SDL_CreateTexture : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    game_window->Type=Rules;
    get_Tittle (game_window->Type , game_window->title);
    SDL_SetWindowTitle(game_window->window, game_window->title);

    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load("img/background.jpg");
    if (NULL == tmp) {
        fprintf(stderr, "Erreur IMG_load: %s", SDL_GetError());
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
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        SDL_DestroyRenderer(game_window->renderer);
        SDL_DestroyWindow(game_window->window);
        SDL_DestroyTexture(game_window->texture);
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    SDL_SetRenderTarget(game_window->renderer,game_window->texture);
    // link btw window's renderer and texture
    SDL_RenderCopy(game_window->renderer,texture,NULL,NULL);
    //cpoy texture onto windows' one
    SDL_DestroyTexture(texture);
    //free texture
    SDL_SetRenderTarget(game_window->renderer,NULL);
    //renderer doesn't point on anything anymore
    SDL_RenderCopy(game_window->renderer,game_window->texture,NULL,NULL);
    //final copy of windows' texture onto renderer
    SDL_RenderPresent(game_window->renderer);
    //renderer is all pretty and ready :)

    //initialize the button
    // x=1516 y=4 w=170 h=70
    SDL_Rect return_but = {1690,1,160,76};
    game_window->Return_b = return_but;

    status = EXIT_SUCCESS;
    return status;
}

int init_character(View_app * app){
    app->Robot.SPEED = 60;
    SDL_Rect temp = {900,500,70,100 };
    app->Robot.Position = temp;
    SDL_Surface * Robot_dst = IMG_Load("./img/Robot.png");
    if (Robot_dst == NULL)
    {
        fprintf(stderr,"Error IMG_load: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_FillRect(Robot_dst,app->Robot.Position,250, 194, 90);
}

/*
int init_character_F_img(View_app * app) {
    SDL_Surface * Robot_still_FB = IMG_Load("./img/RobotWalkFront.png");
    if (Robot_still_FB == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app->Game.renderer, Robot_still_FB);
    if (texture == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetRenderTarget(app->Game.renderer,app->Robot.move_F);
    SDL_RenderCopy(app->Game.renderer,texture,NULL,NULL);
    SDL_SetRenderTarget(app->Game.renderer,NULL);
    SDL_Rect rect2={0,0,Robot_still_FB->w/app->Robot.WALK_PICTURE_NUMBER,Robot_still_FB->h};

    //defines Robot walks fbs rectangle
    for (int i = 0; i<app->Robot.WALK_PICTURE_NUMBER; i++)
    {
        app->Robot.walks_F[i].w = Robot_still_FB->w / app->Robot.WALK_PICTURE_NUMBER;
        app->Robot.walks_F[i].h = Robot_still_FB->h;
        app->Robot.walks_F[i].x = rect2.x + i*app->Robot.walks_F[i].w;
        app->Robot.walks_F[i].y = 0;
    }

    SDL_FreeSurface(Robot_still_FB);
    SDL_DestroyTexture(texture);
    return EXIT_SUCCESS;
}
int init_character_R_img(View_app * app){
    //get image robot right
    SDL_Surface * Robot_right = IMG_Load("./img/RobotWalkRight.png");
    if (Robot_right == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    //init rect in which robot exists
    app->Robot.Position.h=Robot_right->h;
    app->Robot.Position.w=Robot_right->w / app->Robot.WALK_PICTURE_NUMBER;

    //creates robot right texture in the rectangle
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app->Game.renderer, Robot_right);
    if (texture == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_SetRenderTarget(app->Game.renderer,app->Robot.move_R);
    SDL_RenderCopy(app->Game.renderer,texture,NULL,NULL);
    SDL_SetRenderTarget(app->Game.renderer,NULL);
    SDL_Rect rect={0,0,Robot_right->w/app->Robot.WALK_PICTURE_NUMBER,Robot_right->h};

    //defines Robot walks r rectangle
    for (int i = 0; i<app->Robot.WALK_PICTURE_NUMBER; i++)
    {
        app->Robot.walks_R[i].w = Robot_right->w / app->Robot.WALK_PICTURE_NUMBER;
        app->Robot.walks_R[i].h = Robot_right->h;
        app->Robot.walks_R[i].x = rect.x + i*app->Robot.walks_R[i].w;
        app->Robot.walks_R[i].y = 0;
    }

    SDL_FreeSurface(Robot_right);
    SDL_DestroyTexture(texture);
    return EXIT_SUCCESS;
}
int init_character_L_img(View_app * app){

    SDL_Surface * Robot_left = IMG_Load("./img/RobotWalkLeft.png");
    if (Robot_left == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app->Game.renderer, Robot_left);
    if (texture == NULL)
    {
        printf("Error IMG_load: %s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetRenderTarget(app->Game.renderer,app->Robot.move_L);
    SDL_RenderCopy(app->Game.renderer,texture,NULL,NULL);
    SDL_SetRenderTarget(app->Game.renderer,NULL);
    SDL_Rect rect3={0,0,Robot_left->w/app->Robot.WALK_PICTURE_NUMBER,Robot_left->h};

    //defines Robot walks fbs rectangle
    for (int i = 0; i<app->Robot.WALK_PICTURE_NUMBER; i++)
    {
        app->Robot.walks_L[i].w = Robot_left->w / app->Robot.WALK_PICTURE_NUMBER;
        app->Robot.walks_L[i].h = Robot_left->h;
        app->Robot.walks_L[i].x = rect3.x + i*app->Robot.walks_L[i].w;
        app->Robot.walks_L[i].y = 0;
    }
    SDL_FreeSurface(Robot_left);
    SDL_DestroyTexture(texture);
    return EXIT_SUCCESS;
}

int init_character (View_app * app){
    app->Robot.SPEED = 60;
    app->Robot.WALK_PICTURE_NUMBER =8;
    app->Robot.anim_state=0;
    app->Robot.Position.x=900;
    app->Robot.Position.y=500;

    if (init_character_F_img(app)!= EXIT_SUCCESS){
        fprintf(stderr, "error init_character F : %s", SDL_GetError());
    }
    if (init_character_L_img(app)!= EXIT_SUCCESS){
        fprintf(stderr, "error init_character L : %s", SDL_GetError());
    }
    if (init_character_R_img(app)!= EXIT_SUCCESS){
        fprintf(stderr, "error init_character R : %s", SDL_GetError());
    }

    return EXIT_SUCCESS;
}

void personStatic(View_app * app) {
    SDL_RenderCopy(app->Game.renderer,app->Robot.move_F, &app->Robot.walks_F[app->Robot.anim_state], &app->Robot.Position);
    SDL_RenderPresent(app->Game.renderer);
    app->Robot.anim_state = (app->Robot.anim_state + 1) % app->Robot.WALK_PICTURE_NUMBER;
}

void personWalkRight(View_app * app) {
//pos = lien avec model dans controller
    SDL_RenderCopy(app->Game.renderer,app->Robot.move_R, &app->Robot.walks_R[app->Robot.anim_state], &app->Robot.Position);
    SDL_RenderPresent(app->Game.renderer);
    app->Robot.anim_state = (app->Robot.anim_state + 1) % app->Robot.WALK_PICTURE_NUMBER;
    SDL_Delay(app->Robot.SPEED);
}

void personWalkLeft(View_app * app) {
    SDL_RenderCopy(app->Game.renderer,app->Robot.move_L, &app->Robot.walks_L[app->Robot.anim_state], &app->Robot.Position);
    SDL_RenderPresent(app->Game.renderer);
    app->Robot.anim_state = (app->Robot.anim_state + 1) % app->Robot.WALK_PICTURE_NUMBER;
    SDL_Delay(app->Robot.SPEED);
}

void personWalkUp(View_app * app) {
    SDL_RenderCopy(app->Game.renderer,app->Robot.move_F, &app->Robot.walks_F[app->Robot.anim_state], &app->Robot.Position);
    SDL_RenderPresent(app->Game.renderer);
    app->Robot.anim_state = (app->Robot.anim_state + 1) % app->Robot.WALK_PICTURE_NUMBER;
    SDL_Delay(app->Robot.SPEED);
}

void personWalkDown(View_app * app){
    SDL_RenderCopy(app->Game.renderer,app->Robot.move_F, &app->Robot.walks_F[app->Robot.anim_state], &app->Robot.Position);
    SDL_RenderPresent(app->Game.renderer);
    SDL_Delay(app->Robot.SPEED);
    app->Robot.anim_state = (app->Robot.anim_state + 1) % app->Robot.WALK_PICTURE_NUMBER;
}
*/


int init_View(View_app *view_app){
    //executing SDL initialisation and checking it worked
    if (init_SDL()!=EXIT_SUCCESS){
        fprintf(stderr, "error init_Window : %s", SDL_GetError());
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    //ici on pourra initialiser le personnage et les objets aussi par exemple
    return EXIT_SUCCESS;
}