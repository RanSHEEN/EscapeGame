//
// Created by Marie on 12/04/2022.
//

#include "./Controller/controller.h"

#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*
 * Definitions des tests Personnages
 */
static void test_Personnage_move_down(void **state){
    Personage * p = CreatePersonage();
    p->x_position=25;
    p->y_position=25;
    move_down(p,1);
    assert_int_equal(25,p->x_position);
    assert_int_equal(26,p->y_position);
    DeletePersonage(p);
}
static void test_Personnage_move_up(void **state){
    Personage * p = CreatePersonage();
    p->x_position=25;
    p->y_position=25;
    move_up(p,1);
    assert_int_equal(25,p->x_position);
    assert_int_equal(24,p->y_position);
    DeletePersonage(p);
}
static void test_Personnage_move_right(void **state){
    Personage * p = CreatePersonage();
    p->x_position=25;
    p->y_position=25;
    move_right(p,1);
    assert_int_equal(26,p->x_position);
    assert_int_equal(25,p->y_position);
    DeletePersonage(p);
}
static void test_Personnage_move_left(void **state){
    Personage * p = CreatePersonage();
    p->x_position=25;
    p->y_position=25;
    move_left(p,1);
    assert_int_equal(24,p->x_position);
    assert_int_equal(25,p->y_position);
    DeletePersonage(p);
}
/*
 * def test object
 */
static void test_Object_Create(void **state){
    char id[] = "Object_1";
    int x = 5;
    int y = 1;
    char file_name[] = "file_Test";
    Object * o = createObject( id, x, y, file_name,1);
    assert_int_equal(5,o->j);
    assert_int_equal(1,o->i);
    assert_string_equal("Object_1",o->id);
    assert_string_equal("file_Test",o->file_name);
    freeObject(o);
}
/*
 * def test Door
 */
static void test_Door_Create(void **state){
    char id[] = "Porte_1";
    int x = 3;
    int y = 30;
    char file_name[] = "file_Test_Door";
    Door * D =createDoor( id, x, y, file_name);
    assert_int_equal(3,D->j);
    assert_int_equal(30,D->i);
    assert_string_equal("Porte_1",D->id);
    assert_string_equal("file_Test_Door",D->file_name);
    assert_int_equal(0,D->access);
    freeDoor(D);
}
static void test_Door_Change_Access(void **state){
    char id[] = "Porte_1";
    int x = 3;
    int y = 30;
    char file_name[] = "file_Test_Door";
    Door * D =createDoor( id, x, y, file_name);
    changeAccess(D);
    assert_int_equal(1,D->access);
    changeAccess(D);
    assert_int_equal(0,D->access);
    freeDoor(D);
}
static void test_CreateFraming(void **state){
    int nb_j = 9; //nombre de case en largeur
    int nb_i = 4;// nombre de case en hauteur
    int w=SCREEN_W/nb_j;//taille d'une case en largeur
    int h=SCREEN_H/nb_i;//taille d'une case en hauteur
    frame ** tab = CreateFraming(nb_j,nb_i,w,h);
    assert_true(tab[0][0].d==NULL);
    assert_true(tab[0][0].o==NULL);
    assert_int_equal(0,tab[0][0].Pos_x);
    assert_int_equal(0,tab[0][0].Pos_y);
    assert_int_equal(140,tab[0][1].Pos_x);
    assert_int_equal(280,tab[0][2].Pos_x);
    assert_int_equal(140,tab[1][0].Pos_y);
    assert_int_equal(280,tab[2][0].Pos_y);
    assert_int_equal(280,tab[2][2].Pos_x);
    assert_int_equal(280,tab[2][2].Pos_y);
    deleteFraming(tab);
}
static void test_CreateRoom(void **state){
    char * filename= "file";
    char * name="room 1";
    Room * R = CreateRoom(filename,name,2);
    assert_int_equal(4,R->nb_i);
    assert_int_equal(9,R->nb_j);
    assert_int_equal(140,R->w);
    assert_int_equal(140,R->h);
    assert_int_equal(2,R->nb_obj);
    assert_string_equal(filename,R->filename);
    assert_string_equal(name,R->name);
    assert_true(R->framing!=NULL);
    deleteRoom(R);
}
void Test_Empty_PrintRoom(){
    char * filename= "file";
    char * name="room 1";
    Room * R = CreateRoom(filename,name,2);
    printRoom(R);
    deleteRoom(R);
}
static void test_addObject(void **state){
    char * filename= "file";
    char * name="room 1";
    Room * R = CreateRoom(filename,name,5);
    char * id ="obj";
    addObject(R, id, 0, 0,filename, 1);
    addObject(R, id, 3, 8,filename, 1);
    addObject(R, id, 2, 0,filename, 1);
    addObject(R, id, 2, 8,filename, 1);
    assert_true(R->framing[0][0].o!=NULL);
    assert_true(R->framing[3][8].o!=NULL);
    assert_true(R->framing[2][0].o==NULL);
    assert_true(R->framing[2][8].o==NULL);
    deleteRoom(R);
}
static void test_addDoor(void **state){
    char * filename= "file";
    char * name="room 1";
    Room * R = CreateRoom(filename,name,0);
    char * id ="door";
    addDoor(R,id,2, 0,filename);
    addDoor(R,id,2, 8,filename);
    addDoor(R,id,2, 2,filename);
    assert_true(R->framing[2][0].d!=NULL);
    assert_true(R->framing[2][8].d!=NULL);
    assert_true(R->framing[2][2].d==NULL);
    deleteRoom(R);
}
static void test_addDoorOnDoor(void **state){
    char * filename= "file";
    char * name="room 1";
    Room * R = CreateRoom(filename,name,0);
    char * id_d1="door1";
    char * id_d2="door2";
    addDoor(R,id_d1,2,0,filename);
    addDoor(R,id_d2,2,0,filename);
    assert_string_equal(R->framing[2][0].d->id,id_d1);
    deleteRoom(R);
}
static void test_addObjectOnObject(void **state){
    char * filename= "file";
    char * name="room 1";
    Room * R = CreateRoom(filename,name,2);
    char * id_o1="obj1";
    char * id_o2="obj2";
    addObject(R, id_o1, 0, 0,filename, 1);
    addObject(R, id_o2, 0, 0,filename, 1);
    assert_string_equal(R->framing[0][0].o->id,id_o1);
    deleteRoom(R);
}
void Test_notEmpty_PrintRoom(){
    char * filename= "file";
    char * name="room 1";
    Room * R = CreateRoom(filename,name,4);
    char * id_d="door";
    char * id_o ="obj";
    addDoor(R,id_d,2, 0,filename);
    addDoor(R,id_d,2, 8,filename);
    addObject(R, id_o, 0, 0,filename, 1);
    addObject(R, id_o, 3, 8,filename, 1);
    addObject(R, id_o, 3, 4,filename, 1);
    addObject(R, id_o, 2, 2,filename, 1);
    printRoom(R);
    deleteRoom(R);
}
static void test_isInteractionPossible(void **state){
    Personage * p =CreatePersonage();
    Room * R =CreateRoom("filename","name",1);
    addObject(R,"obj",1,2,"filename",1);
    addDoor(R,"door",2,0,"filename");

    //personnage sur l'objet
    p->x_position=315;
    p->y_position=160;
    int * res = isInteractionPossible(p,R);
    //printf("%d,%d,%d\n",res[0],res[1],res[2]);
    assert_int_equal(res[0],1);
    assert_int_equal(res[1],2);
    assert_int_equal(res[2],1);

    //personnage sur la porte
    p->x_position=35;
    p->y_position=300;
    res = isInteractionPossible(p,R);
    //printf("%d,%d,%d\n",res[0],res[1],res[2]);
    assert_int_equal(res[0],2);
    assert_int_equal(res[1],0);
    assert_int_equal(res[2],2);

    //personnage à gauche de l'objet
    p->x_position=245;
    p->y_position=210;
    res = isInteractionPossible(p,R);
    //printf("%d,%d,%d\n",res[0],res[1],res[2]);
    assert_int_equal(res[0],1);
    assert_int_equal(res[1],2);
    assert_int_equal(res[2],1);

    //personnage à droite de la porte
    p->x_position=105;
    p->y_position=350;
    res = isInteractionPossible(p,R);
    //printf("%d,%d,%d\n",res[0],res[1],res[2]);
    assert_int_equal(res[0],2);
    assert_int_equal(res[1],1);
    assert_int_equal(res[2],0);

    //personnage en bas de l'objet
    p->x_position=315;
    p->y_position=230;
    res = isInteractionPossible(p,R);
    //printf("%d,%d,%d\n",res[0],res[1],res[2]);
    assert_int_equal(res[0],1);
    assert_int_equal(res[1],2);
    assert_int_equal(res[2],1);

    //personnage en haut de la porte
    p->x_position=35;
    p->y_position=230;
    res = isInteractionPossible(p,R);
    //printf("%d,%d,%d\n",res[0],res[1],res[2]);
    assert_int_equal(res[0],1);
    assert_int_equal(res[1],0);
    assert_int_equal(res[2],0);
}

int main(void){
   /**
    * Test Personnage and Object
    */
    const struct CMUnitTest tests_object_Door_Personnage[]={
            cmocka_unit_test(test_Object_Create),
            cmocka_unit_test(test_Door_Create),
            cmocka_unit_test(test_Door_Change_Access),
            cmocka_unit_test(test_Personnage_move_down),
            cmocka_unit_test(test_Personnage_move_up),
            cmocka_unit_test(test_Personnage_move_left),
            cmocka_unit_test(test_Personnage_move_right),
            cmocka_unit_test(test_CreateFraming),
            cmocka_unit_test(test_CreateRoom),
            cmocka_unit_test(test_addObject),
            cmocka_unit_test(test_addDoor),
            cmocka_unit_test(test_addDoorOnDoor),
            cmocka_unit_test(test_addObjectOnObject),
            cmocka_unit_test(test_isInteractionPossible)
    };
    Test_notEmpty_PrintRoom();
    return cmocka_run_group_tests_name("test Objet",tests_object_Door_Personnage,NULL,NULL);

}
