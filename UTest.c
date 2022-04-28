//
// Created by eii on 12/04/2022.
//

#include "./Controller/controller.h"
#include "./View/main_view.h"
#include "./Model/main_model.h"

#include <stdarg.h>
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
    move_down(p);
    assert_int_equal(25,p->x_position);
    assert_int_equal(24,p->y_position);
    DeletePersonage(p);
}
static void test_Personnage_move_up(void **state){
    Personage * p = CreatePersonage();
    p->x_position=25;
    p->y_position=25;
    move_up(p);
    assert_int_equal(25,p->x_position);
    assert_int_equal(26,p->y_position);
    DeletePersonage(p);
}
static void test_Personnage_move_right(void **state){
    Personage * p = CreatePersonage();
    p->x_position=25;
    p->y_position=25;
    move_right(p);
    assert_int_equal(26,p->x_position);
    assert_int_equal(25,p->y_position);
    DeletePersonage(p);
}
static void test_Personnage_move_left(void **state){
    Personage * p = CreatePersonage();
    p->x_position=25;
    p->y_position=25;
    move_left(p);
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
    int y = 50;
    char file_name[] = "file_Test";
    Object * o = createObject( id, x, y, file_name);
    assert_int_equal(5,o->x);
    assert_int_equal(50,o->y);
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
    assert_int_equal(3,D->x);
    assert_int_equal(30,D->y);
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



int main_POD(void){
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
    };
    return cmocka_run_group_tests_name("test Objet",tests_object_Door_Personnage,NULL,NULL);

}
