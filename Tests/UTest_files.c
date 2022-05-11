//
// Created by Marie on 06/05/22.
//
#include "../Model/model.h"

#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void test_OpenCloseFiles(void **state){
    char * path = "../Files_descriptors/ForTests.txt";
    char * wrong_path = "../Files_descriptors/non_existent.txt";
    FILE * f1 = openFileRead(path);
    FILE * f2 = openFileRead(wrong_path);
    assert_true(f1!=NULL);
    assert_true(f2==NULL);
    closeFile(f1);
}
static void test_readLine(void **state){
    char * path = "../Files_descriptors/ForTests.txt";
    FILE * f1 = openFileRead(path);
    char * tampon = (char *) malloc(sizeof(char)*TMAX);
    readFileLine(f1,tampon);
    char * line1="I am a line\n";
    assert_string_equal(tampon,line1);
    readFileLine(f1,tampon);
    char * line2="I am a 2nd line";
    assert_string_equal(tampon,line2);
}
static void test_readLineGraph(void **state){
    VertexList * g = initGraph();

    char * tampon1 = "Vertex - label:v1 - enigma_number:1\n";
    char * tampon2 = "Vertex - label:v2 - enigma_number:2\n";

    readGraphFileLine(tampon1,g);
    assert_string_equal("v1",g->first->label);
    assert_string_equal("v1",g->last->label);
    assert_int_equal(1,g->first->enigma_number);

    readGraphFileLine(tampon2,g);
    assert_string_equal("v1",g->first->label);
    assert_string_equal("v2",g->last->label);
    assert_int_equal(1,g->first->enigma_number);
    assert_int_equal(2,g->last->enigma_number);

    char * tampon3 = "Edge - v1 - v2 - obj_label:obj1";
    char * tampon4 = "Edge - v1 - v2 - obj_label:obj2";

    readGraphFileLine(tampon3,g);
    assert_string_equal("obj1",g->first->connect->first->obj_label);
    assert_string_equal("obj1",g->first->connect->last->obj_label);

    readGraphFileLine(tampon4,g);
    assert_string_equal("obj1",g->first->connect->first->obj_label);
    assert_string_equal("obj2",g->first->connect->last->obj_label);

    char * tampon5 = "pwet - jgdhdkjygzhef";
    readGraphFileLine(tampon5,g);

    printGraph(g);
}
static void test_readGraphFile(void **state){
    char * PATH = "../Files_descriptors/Graph_Tests.txt";
    VertexList * g =readGraphFile(PATH);
    printGraph(g);
}
static void test_readRoomFileLine(void **state){
    char * filename = "PATH";
    char * name = "NAME";
    Room * R =CreateRoom(filename,name,2);
    char * tampon1="Door - id : door1 - Position : (2;0) - filename : Path";
    char * tampon2="Door - id : door2 - Position : (2;8) - filename : Path";

    readRoomFileLine(tampon1, R);
    assert_true(R->framing[2][0].d!=NULL);
    readRoomFileLine(tampon2, R);
    assert_true(R->framing[2][8].d!=NULL);

    char * tampon3="Object - id : obj1 - Position : (0;0) - filename : Path - Type : 1";
    char * tampon4="Object - id : obj2 - Position : (2;5) - filename : Path - Type : 1";

    readRoomFileLine(tampon3, R);
    assert_true(R->framing[0][0].o!=NULL);
    readRoomFileLine(tampon4, R);
    assert_true(R->framing[2][5].o!=NULL);

    printRoom(R);
}
static void test_readRoomFile(void **state){
    char * PATH = "../Files_descriptors/Room_Tests.txt";
    Room * R =readRoomFile(PATH);
    printRoom(R);
}

int main(void){

    const struct CMUnitTest tests_file[]={
            cmocka_unit_test(test_OpenCloseFiles),
            cmocka_unit_test(test_readLine),
            cmocka_unit_test(test_readLineGraph),
            cmocka_unit_test(test_readGraphFile),
            cmocka_unit_test(test_readRoomFileLine),
            cmocka_unit_test(test_readRoomFile)
    };
    return cmocka_run_group_tests_name("test Objet",tests_file,NULL,NULL);

}