//
// Created by Marie on 04/05/22.
//

#include "./Controller/controller.h"
#include "./View/main_view.h"
#include "./Model/model.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*
 * def change State tests
 */
static VertexList * ForTest(){
    VertexList * g= (VertexList *) malloc(sizeof(VertexList));
    initGraph(g);
    char * label2="Vertex2";
    char * label1="Vertex1";
    char * label3="Vertex3";
    char * w="win";
    insertFirstVertex(g,label2,1);
    insertFirstVertex(g,label1,2);
    insertLastVertex(g,label3,1);
    insertLastVertex(g,w,0);
    char * obj1="Object1";
    char * obj2="Object2";
    char * obj3="Object3";
    char * obj4="Object4";
    addLink(findVertex(g,label1),findVertex(g,label2),obj1);
    addLink(findVertex(g,label1),findVertex(g,label3),obj2);
    addLink(findVertex(g,label3),findVertex(g,w),obj3);
    addLink(findVertex(g,label2),findVertex(g,w),obj4);
    setOnFirstVertex(g);
    return g;
}
static void Test_Change_inf(){
    VertexList * g = ForTest();
    char id[] = "Object1";
    int x = 5;
    int y = 50;
    char file_name[] = "file_Test";
    Object * o = createObject( id, x, y, file_name, 1);
    int a = SolvedEnigma(g,o);
    assert_int_equal(a,0);
}
static void Test_Change_sup(){
    VertexList * g = ForTest();
    char id[] = "Object1";
    int x = 5;
    int y = 50;
    char file_name[] = "file_Test";
    Object * o = createObject( id, x, y, file_name,1);
    g->current->enigma_solved=3;
    int a = changeState(g,o);
    assert_int_equal(a,-1);
}
static void Test_Change_egal_one_win(){
    VertexList * g = ForTest();
    setOnNextVertex(g); //Vertex2
    char id[] = "Object4";
    int x = 5;
    int y = 50;
    char file_name[] = "file_Test";
    Object * o = createObject( id, x, y, file_name,1);
    int a = SolvedEnigma(g,o);
    assert_int_equal(a,1);
}
static void Test_Change_egal_more(){
    VertexList * g = ForTest();
    char id[] = "Object1";
    int x = 5;
    int y = 50;
    char file_name[] = "file_Test";
    Object * o = createObject( id, x, y, file_name,1);

    int a = SolvedEnigma(g,o);
    assert_int_equal(a,0);
    int b= SolvedEnigma(g,o);
    assert_int_equal(b,1);
}

int main(void){
    /**
     * Test Graph : EdgeList
     */
    const struct CMUnitTest tests[]={
            cmocka_unit_test(Test_Change_inf),
            cmocka_unit_test(Test_Change_sup),
            cmocka_unit_test(Test_Change_egal_one_win),
            cmocka_unit_test(Test_Change_egal_more)
    };
    return cmocka_run_group_tests_name("test State",tests,NULL,NULL);
}