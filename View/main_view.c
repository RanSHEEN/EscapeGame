
#include "main_view.h"


/* this function initialises the window and creates the texture/renderer for the menu
 * + allows to close it using the close tab button */
/*int init_window(){
}

int free_window (Menu_windows * escape){

}*/

int main(){
    Menu_windows menu;
    menu.SCREEN_WIDTH=1746;
    menu.SCREEN_HEIGHT=984;
    Launch_view(&menu);
    Game_Window(&menu);
}
