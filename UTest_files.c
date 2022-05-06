//
// Created by Marie on 06/05/22.
//
#include "./Controller/controller.h"

#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void test_OpenCloseFiles(void **state){
    char * path = "./Files_descriptors/ForTests.txt";
    char * wrong_path = "./Files_descriptors/non_existent.txt";
    FILE * f1 = openFileRead(path);
    FILE * f2 = openFileRead(wrong_path);
    assert_true(f1!=NULL);
    assert_true(f2==NULL);
    closeFile(f1);
}
static void test_readLine(void **state){
    char * path = "./Files_descriptors/ForTests.txt";
    FILE * f1 = openFileRead(path);
    char * tampon = (char *) malloc(sizeof(char)*TMAX);
    readFileLine(f1,tampon);
    char * line1="I am a line\n";
    assert_string_equal(tampon,line1);
    readFileLine(f1,tampon);
    char * line2="I am a 2nd line";
    assert_string_equal(tampon,line2);
}

int main(void){

    const struct CMUnitTest tests_object_Door_Personnage[]={
            cmocka_unit_test(test_OpenCloseFiles),
            cmocka_unit_test(test_readLine)
    };
    return cmocka_run_group_tests_name("test Objet",tests_object_Door_Personnage,NULL,NULL);

}