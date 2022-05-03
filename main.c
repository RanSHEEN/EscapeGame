//
// Created by eii on 06/04/2022.
//
#include "./Controller/controller.h"
#include "./View/main_view.h"
#include "./Model/model.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>



int main(){
    //declaring our windows
    View_app app;

    if (init_SDL()!=EXIT_SUCCESS){
        fprintf(stderr, "error init_Window : %s", SDL_GetError());
        SDL_Quit();
        IMG_Quit();
        return EXIT_FAILURE;
    }
    main_controller(&app);

    free_view (&app);

    return EXIT_SUCCESS;
}

