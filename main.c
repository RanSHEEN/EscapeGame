//
// Created by eii on 06/04/2022.
//
#include "./Controller/controller.h"

int main(void){
    //declaring our windows
    View_app app;

    if (init_View(&app)!=EXIT_SUCCESS){
        fprintf(stderr, "error init_Window : %s", SDL_GetError());
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    main_controller(&app);
    Personage * p = CreatePersonage();

    printf("%d\n", p->x_position);

    free_view (&app);

    return EXIT_SUCCESS;
}

