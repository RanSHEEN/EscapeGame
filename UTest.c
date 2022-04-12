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


static void test_Personnage(void **state){
    Personage * p = CreatePersonage();

    move_down(p);
    assert_int_equal(0,p->x_position);
    assert_int_equal(983,p->y_position);
    move_up(p);
    assert_int_equal(0,p->x_position);
    assert_int_equal(984,p->y_position);
    move_right(p);
    assert_int_equal(1,p->x_position);
    assert_int_equal(984,p->y_position);
    move_left(p);
    assert_int_equal(0,p->x_position);
    assert_int_equal(984,p->y_position);

    DeletePersonage(p);
}

static void test_Object(void **state){
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

static void test_Door(void **state){
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
    changeAccess(D);
    assert_int_equal(1,D->access);
    changeAccess(D);
    assert_int_equal(0,D->access);
    freeDoor(D);
}

int main(void){
    const struct CMUnitTest tests[]={
            cmocka_unit_test(test_Personnage),
            cmocka_unit_test(test_Object),
            cmocka_unit_test(test_Door)
    };

    return cmocka_run_group_tests_name("test",tests,NULL,NULL);
}
